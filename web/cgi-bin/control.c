#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sys/ipc.h>
#include <strings.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <unistd.h>
#include <fcntl.h>

#define COMMAND_MAX 1
#define MQ_KEY_PATH "/lib"
#define MQ_KEY_CHAR 'A'
#define MQ_MSGBUF_LEN 50

/********命令种类**********
 * 字符串格式：（分号“；”是格式内一部分）
 * ；设备号；命令id；命令值；
 * ******命令种类 end ****/
#define CMD_CHANSHI_ID 1

typedef struct mqbuf
{
        long type;
        char msg[MQ_MSGBUF_LEN];
}MSG;

typedef struct
{
    char type[5];
    char shebei[10];
    char value[2];
}CMD;


/* ***********
 * 获取命令
 * ***********/
bool getCommand(char * data,char (*cmd)[50],int len)
{
    char *p = data;
    char cmdNum[10] = {0};
    bool getCmd = false;
    int cmd_count = 0;
    if(len > 0){
        //铲屎
        while (*p != '\0') {
            if(*p == 'c'){
                if (0 == memcmp(p,"chanshi=start",strlen("chanshi=start") )) {
                    p += strlen("chanshi=start");
                    while (*p != '\0') {
                        if (*p == 'n') {
                            if (0 == memcmp(p,"num=",strlen("num="))) {
                                p += strlen("num=");
                                int i = 0;
                                while(*p != '&' && *p != '\0' && i < 9){
                                    cmdNum[i] = *p;
                                    i++;
                                    p++;
                                }
                                if (i > 0){
                                    sprintf(cmd[cmd_count],";%d;%s;%d;",CMD_CHANSHI_ID,cmdNum,1);
                                    getCmd = true;
                                    cmd_count++;
                                    break;
                                }

                            }

                        }
                        p++;
                    }
                }

            }
            p++;
        }

    }
    return getCmd;
}

bool getSendMsg(CMD *cmd,char *data)
{
    if(strlen(data) > 50){
        return false;
    }
    char *p = data;
    p++;
    int i = 0;
    while(*p++ != ';' && i++ < sizeof(cmd->type) - 1){
        cmd->type[i-1] = *(p - 1);
    }
    i = 0;
    while(*p++ != ';' && i++ < sizeof(cmd->shebei) - 1){
        cmd->shebei[i-1] = *(p - 1);
    }
    i = 0;
    while(*p++ != ';' && i++ < sizeof(cmd->value) - 1){
        cmd->value[i-1] = *(p -1);
    }
    return true;
}


/* ***********
 * 任务处理
 * ***********/
int processTask(char (*cmd)[50])
{

    key_t key = ftok(MQ_KEY_PATH,MQ_KEY_CHAR);
    int msgid = msgget(key,O_RDWR);
    if (msgid <= 0){
        printf("服务器消息队列崩溃！\n");
        return 0;
    }
    MSG buf;
    int i = 0;
    for(;i < COMMAND_MAX ;i++){
        printf("%s",cmd[i]);
        if(cmd[i][0] == ';'){
            bzero(&buf,sizeof(buf));
            CMD command;

            if(getSendMsg(&command,cmd[i])){
                buf.type = atol(command.type);
                sprintf(buf.msg,";%s;%s;",command.shebei,command.value);
                msgsnd(msgid,&buf,MQ_MSGBUF_LEN,0);
                printf("send msg type:%ld,msg:%s\n",buf.type,buf.msg);
            }
//            if ( buf.type > 0){
//                strcpy(buf.msg,getMsg(p));

//            }

        }
    }
    return 1;

}

int main()
{
    //web
    size_t i = 0,n = 0;
    char num[10] = {"0"};
    char *method = NULL;
    char command[COMMAND_MAX][50] = {0};
    //获取HTTP请求方法(POST/GET)
    if (NULL == (method = getenv("REQUEST_METHOD")))
    {
        return 0;
    }
    printf("content-type:text/html;charset=utf-8\n\n");
    printf("<TITLE>注册结果</TITLE>");
    //POST 方法解析,从 STDIN_FILENO 动态获取数据
    if (getenv("CONTENT_LENGTH") && strcmp(method,"POST") == 0){
        n = atoi(getenv("CONTENT_LENGTH"));
        size_t length = n * sizeof(char) + 1;
        //必须申请缓存，因为stdin是不带缓存的。
        char * inputdata = (char *)malloc(length);
        if(inputdata){
            memset((void*)inputdata,0,length);
            //从标准输入读取一定数据
            fread(inputdata, sizeof(char), length, stdin);
            //获取命令
            if(getCommand(inputdata,command,length)){
                printf("cmd is : %s\n",command[0]);
                processTask(command);
            }else{
                printf("任务解析失败\n");
            }
            free(inputdata);
        }
    }else if (getenv("QUERY_STRING") && strcmp(method,"GET") == 0){
        //环境变量的长度有限,导致GET方法传送数据被限制
        char * inputdata = getenv("QUERY_STRING");
        if (inputdata == NULL){
            printf("<p>错误：数据没有被输入或数据传输发生错误</p>");
        }else{
            int length = strlen(inputdata);
   //         printf("+++html data len = %d++%s+++",strlen(inputdata),inputdata);
            //获取命令
            if(getCommand(inputdata,command,length)){
                printf("cmd is : %s\n",command[0]);
                processTask(command);
            }else{
                printf("任务解析失败\n");
            }

         //   sscanf(inputdata,"username=%[^&]&password=%s",name,pwd);
        }

    }else{
          printf("%s\n","bad request!");
          return 0;
    }

    printf("<meta http-equiv=\"Refresh\" content=\"5;URL=/control.html?num=%s\">",num);

}
