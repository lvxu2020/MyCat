#include "mqttMsg.h"

#define PORT 1883
#define ADDRESS "127.0.0.1"
#define ID "99"
#define TOPIC "cat"

//每次用到此值时从寄存器重新读取，而不是在缓存中拿数据
volatile MQTTClient_deliveryToken deliveredtoken;

void * mqttMsgRec(void *p)
{
    MQTTClient client;
    const int qos = 1;
    const long timeout = 10000L;
    char buf[128];
    int port = PORT;
    char address[128] = {ADDRESS};
    char sub_id[128] = {"98"};
    char topic[128] = {TOPIC};

    MQTTClient_connectOptions conn_opts=MQTTClient_connectOptions_initializer;
//    if (opt_init(&port,address,sub_id,topic)<0) {
//        printf("opt_init failure:%s\n",strerror(errno));
//        return 1;
//    }
    snprintf(buf,sizeof(buf),"tcp://%s:%d",address,port);
    //创建链接
    MQTTClient_create(&client,buf,sub_id,MQTTCLIENT_PERSISTENCE_NONE,NULL);
    conn_opts.keepAliveInterval=20;
    conn_opts.cleansession=1;
    //设置回调函数
    MQTTClient_setCallbacks(client,NULL,connlost,msgarrvd,delivered);
    int rc;
    if((rc=MQTTClient_connect(client,&conn_opts))!=MQTTCLIENT_SUCCESS){
        printf("MQTTClient_connect failure:%s\n",strerror(errno));
        return -1;
    }
    printf("Subscribe to topic %s for client %s using QOS %d\n",topic,sub_id,qos);
    MQTTClient_subscribe(client,topic,qos);
    while (1) {
        sleep(3);
        printf("chu li ren wu lou! \n");
    }
}

void * mqttMsgSend(void *p)
{

    MQTTClient client;
    const int qos = 1;
    const long timeout = 1000L;
    char buf[128] = {"****lvxu ke tai NB le"};
    int port = PORT;
    char address[128] = {ADDRESS};
    char address_s[128];
    char pub_id[128] = {"99"};
    char topic[128] = {TOPIC};
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
    while (1) {
        publish_msg.payload=(void *)buf;
        publish_msg.payloadlen=strlen(buf);
        MQTTClient_publishMessage(client,topic,&publish_msg,&token);
        rv=MQTTClient_waitForCompletion(client,token,timeout);
        printf("Message with delivery token %d delivered\n",rv);
        sleep(1);
    }

}

int opt_init(int *port, char address[], char id[], char topic[])
{
    int fd = open(CONFIG_PATH,"r");
    if (fd == -1){//默认设置。
        *port = PORT;
        strcpy(address,ADDRESS);
        strcpy(id,ID);
        strcpy(topic,TOPIC);
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

int msgarrvd(void *context,char *topicName,int topicLen,MQTTClient_message *message)
{
    char *payloadptr = message->payload;
    char getMsgBuf[128] = {'\0'};
    printf("Message arrived \n");
    printf("topic:%s\n",topicName);
    printf("Original Message :%s\n",message->payload);
    printf("analysis Message :");
    int i;
    for (i=0; i < message->payloadlen; i++) {
        getMsgBuf[i] = *payloadptr;
        putchar(*payloadptr++);
    }
    printf("\ngetMsgBuf :%s\n",getMsgBuf);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;

}








