#include "mqttMsg.h"

#define PORT 1883
#define ADDRESS "127.0.0.1"
#define TOPIC_S_C "sToC_"
#define TOPIC_C_S "cToS"

threadpool_t *pool = NULL;
//每次用到此值时从寄存器重新读取，而不是在缓存中拿数据
volatile MQTTClient_deliveryToken deliveredtoken;

void * mqttMsgRec(void *p)
{

    MQTTClient client;
    const int qos = 1;
    const long timeout = 5000L;
    char buf[128];
    int port = PORT;
    char address[128] = {ADDRESS};
    char sub_id[128] = {'\0'};
    getID(sub_id);
    char topic[128] = {TOPIC_C_S};

    MQTTClient_connectOptions conn_opts=MQTTClient_connectOptions_initializer;
    if (opt_init(&port,address,sub_id,topic) < 0) {
        printf("opt_init failure:%s\n",strerror(errno));
        return 1;
    }
    snprintf(buf,sizeof(buf),"tcp://%s:%d",address,port);
    //创建链接
    MQTTClient_create(&client,buf,sub_id,MQTTCLIENT_PERSISTENCE_NONE,NULL);
    conn_opts.keepAliveInterval=20;
    conn_opts.cleansession=1;
    //设置回调函数
    MQTTClient_setCallbacks(client,NULL,connlost,msgarrvd,NULL);
    int rc;
    if((rc=MQTTClient_connect(client,&conn_opts))!=MQTTCLIENT_SUCCESS){
        printf("MQTTClient_connect failure:%s\n",strerror(errno));
        return -1;
    }
    printf("Subscribe to topic %s for client %s using QOS %d\n",topic,sub_id,qos);
    MQTTClient_subscribe(client,topic,qos);    
    while (pool == NULL) {
        /*创建线程池，池里最小3个线程，最大100，队列最大100*/
        pool = threadpool_create(3,100,100);
        sleep(1);
    }
    printf("pool creat succeed!\n");
    while (1) {
        sleep(10);
        printf(" 挂机 \n");
    }

}

void * mqttMsgSend(void *p)
{

    MQTTClient client;
    const int qos = 1;
    const long timeout = 1000L;
    qData task;
    int port = PORT;
    char address[128] = {ADDRESS};
    char address_s[128];
    char pub_id[128] = {'\0'};
    getID(pub_id);
    char topic[128] = {'\0'};
    char sendBuf[128] = {'\0'};
    snprintf(address_s,sizeof(address_s),"tcp://%s:%d",address,port);
    MQTTClient_connectOptions conn_opts=MQTTClient_connectOptions_initializer;
    MQTTClient_message publish_msg=MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    conn_opts.keepAliveInterval=60;
    conn_opts.cleansession=1;
    MQTTClient_create(&client,address_s,pub_id,MQTTCLIENT_PERSISTENCE_NONE,NULL);
    int rv;
    if((rv=MQTTClient_connect(client,&conn_opts))!=MQTTCLIENT_SUCCESS){
        printf("MQTTClient_connect error:%s\n",strerror(errno));
        return -1;
    }
    publish_msg.qos=qos;
    publish_msg.retained=0;
    myQueue *sendQ_ptr = getQueue();

    while (1) {
        bzero(&task,sizeof(task));
        if( !getPubTask(sendQ_ptr,&task) ){
            continue;
        }
        bzero(topic,sizeof(topic));
        sprintf(topic,"%s%d",TOPIC_S_C,task.N);
        bzero(sendBuf,sizeof(sendBuf));
        sprintf(sendBuf,"%d;%s",task.id,task.buf);
        publish_msg.payload=(void *)sendBuf;
        publish_msg.payloadlen=strlen(sendBuf);
        MQTTClient_publishMessage(client,topic,&publish_msg,&token);
        rv=MQTTClient_waitForCompletion(client,token,timeout);
    }

}

void getID(char *time)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);//获取1970-1-1到现在的时间结果保存到tv中
    snprintf(time,128,"id:%ld,%ld",tv.tv_sec,tv.tv_usec);
}

int opt_init(int *port, char address[], char id[], char topic[])
{
    int fd = open(CONFIG_PATH,"r");
    if (fd == -1){//默认设置。

        return 1;
    }else{//重文件中读取数据赋值，最近在考虑是否json化配置文件。此处先不写。
        return 1;
    }
}

void delivered(void *context,MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n",dt);
    deliveredtoken=dt;
}

/*******connlost**********
 * 与服务器断开练级时此函数触发
 * 一般在重名id链接服务器时会
 * 触发此函数，可以在此函数内
 * 调用从连服务器，从新订阅消息
 * 的逻辑
 ************************/
void connlost(void *context,char *cause)
{
    printf("Connection lost\n");
    printf("cause %s\n",cause);
}

/********************************
 * cTos:125;1;数据;
 * 上面为报文格式.
 ****************************** */
bool analysisTask(DataFromClient *task,char *data)
{
    printf("analysisTask in %s\n",data);
    char *p = data;
    char id[10] = {'\0'};
    char type[10] = {'\0'};
    if (0 != memcmp(p,C_TO_S_HEAD,strlen(C_TO_S_HEAD))) {
        return false;
    }
    p += strlen(C_TO_S_HEAD);
    int i = 0;
    while (*p != ';' && i < 9) {//小于9保证最后一位有\0
        id[i++] = *p++;
    }
    task->id = atoi(id);
    if(*p++ != ';'){
        return false;
    }
    i = 0;
    while (*p != ';' && i < 9) {//小于9保证最后一位有\0
        type[i++] = *p++;
    }
    task->type = atoi(type);
    printf("task->type is %d \n",task->type);
    if(*p++ != ';'){
        return false;
    }
    i = 0;
    while (*p != ';' && i < REC_BUF_MAX -1) {//保证最后一位有\0
        task->buf[i++] = *p++;
    }
    if(*p++ != ';'){
        return false;
    }else{
        return true;
    }
}
/**************************
 * 周期性上传，丢几次没事
 * ********************** */
void *statusUpdate(void *arg)
{
    DataFromClient *p = (DataFromClient *)arg;
    int n = strlen(p->buf);
    n = n < REC_BUF_MAX ? n: REC_BUF_MAX;
    char path[128] = {'\0'};
    sprintf(path,"%s/%d/%s",USER_CONF_PATH,p->id,STATUS);
    int fd = open(path,O_WRONLY);
    if (fd < 0) {
        return ;
    }
    lseek(fd,0,SEEK_SET);//定位在文档开头
    write(fd,p->buf,n);
    close(fd);
}

/* *****************
 *解析收到的mqqt字符串
 *放入线程池的队列中
 **************** */
void pushTaskPool(char *data)
{
    lock_pool_mutex(pool);
    //队列中保存的是指针，所以得申请个空间存参数。线程昨晚任务会释放掉这个参数
    DataFromClient *p = (DataFromClient *)malloc(sizeof(DataFromClient));
    if(!analysisTask(p,data)){
        return;
    }
    printf("++++++++jiexichengong++++task.id is %d+\n",p->id);
    switch (p->type) {
    case 0:{//消息上报，写在本地文件中
        threadpool_add(pool, statusUpdate, (void *)p);/* 向任务队列中， 添加一个任务 */
    }break;
    default :break;
    }
    unlock_pool_mutex(pool);
}

int msgarrvd(void *context,char *topicName,int topicLen,MQTTClient_message *message)
{
    char *payloadptr = message->payload;
    char getMsgBuf[128] = {'\0'};
//    printf("Message arrived \n");
//    printf("topic:%s\n",topicName);
//    printf("Original Message :%s\n",message->payload);
//    printf("analysis Message :");
    int i;
    for (i=0; i < message->payloadlen; i++) {
        getMsgBuf[i] = *payloadptr;
        putchar(*payloadptr++);
    }
    printf("\ngetMsgBuf lvxu:%s\n",getMsgBuf);
    pushTaskPool(getMsgBuf);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;

}

bool getPubTask(myQueue *sendQ_ptr,qData *out)
{
    if(is_empty(sendQ_ptr)){
        //业务逻辑暂时没那么多，先加一秒延时挂机等待
        sleep(1);
        return false;
    }
    if(De_Queue(sendQ_ptr,out)){
        printf("getTask success! type:%d,%s\n",out->N,out->buf);
        return true;
    }else {
        return false;
    }
}








