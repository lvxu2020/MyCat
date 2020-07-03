#include "control.h"
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


void * remoteCmd(void *p)
{
   int recId = getMqId(MQ_KEY_PATH,MQ_KEY_CHAR);
   if (recId < 0) {
       return -1;
   }
   MSG recBuf;
   int n;
   printf("queue start !!!\n");
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
