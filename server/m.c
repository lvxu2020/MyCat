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

#define MQ_KEY_PATH "/lib"
#define MQ_KEY_CHAR 'A'
#define MQ_MSGBUF_LEN 50

typedef struct mqbuf
{
        long type;
        char msg[MQ_MSGBUF_LEN];
}MSG;

int getMqId(char *path,char ch);
int processTask(MSG *p);

int main()
{
   int recId = getMqId(MQ_KEY_PATH,MQ_KEY_CHAR);
   if (recId < 0) {
       return -1;
   }
   MSG recBuf;
   int n;
   printf("i start rec\n");
   while (1) {
        n = msgrcv(recId,&recBuf,MQ_MSGBUF_LEN,0,0);
        if (n != -1){
            processTask(&recBuf);
        }

   }

}

int getMqId(char *path,char ch)
{
    key_t key = ftok(MQ_KEY_PATH,MQ_KEY_CHAR);
    int msgid = msgget(key,O_RDWR);
    if (msgid >= 0) {
        msgctl(msgid,IPC_RMID,NULL);
        printf("clear\n");
    }
    msgid = msgget(key,IPC_CREAT|0664);
    return msgid;
}

int processTask(MSG *p)
{
    printf("rec:type=%ld,msg=%s\n",p->type,p->msg);
}
