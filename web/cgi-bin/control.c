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

typedef struct mqbuf
{
        long type;
        char msg[MQ_MSGBUF_LEN];
}MSG;

/* ***********
 * 任务处理
 * ***********/
bool addQueue(int num,int cmd)
{
    printf("+++mun : %d,cmd : %d",num,cmd);
}

/* ***********
 * 获取命令
 * ***********/
bool getCommand(char * data,char (*cmd)[50],int len)
{
    if(len > 0){
        sscanf(data,"stitcw=%[^=]",cmd[0]);

    }
    return len > 0 ? false : true;
}

/* ***********
 * 任务处理
 * ***********/
void processTask(char *task)
{

    key_t key = ftok(MQ_KEY_PATH,MQ_KEY_CHAR);
    int msgid = msgget(key,O_RDWR);
    MSG buf;
    bzero(&buf,sizeof(buf));
    buf.type = 3;
    strcpy(buf.msg,task);
    msgsnd(msgid,&buf,MQ_MSGBUF_LEN,0);

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
            getCommand(inputdata,command,length);
            free(inputdata);
        }
    }else if (getenv("QUERY_STRING") && strcmp(method,"GET") == 0){
        //环境变量的长度有限,导致GET方法传送数据被限制
        char * inputdata = getenv("QUERY_STRING");
        if (inputdata == NULL){
            printf("<p>错误：数据没有被输入或数据传输发生错误</p>");
        }else{
            int length = strlen(inputdata);
            printf("+len = %d++%s+++",strlen(inputdata),inputdata);
            //获取命令
            getCommand(inputdata,command,length);
            processTask(inputdata);
         //   sscanf(inputdata,"username=%[^&]&password=%s",name,pwd);
        }

    }else{
          printf("%s\n","bad request!");
          return 0;
    }
//    //任务处理
//    processTask(command);
    printf("<meta http-equiv=\"Refresh\" content=\"5;URL=/control.html?num=%s\">",num);

}
