#include "control.h"

myQueue *sendQ_ptr = NULL;

void * remoteCmd(void *p)
{
   int recId = getMqId(MQ_KEY_PATH,MQ_KEY_CHAR);
   sendQ_ptr = getQueue();
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
    char buf[32];
    snprintf(buf,32,"%d;%s",p->type,p->msg);
    if(full_queue(sendQ_ptr)){
       Empty_Queue(sendQ_ptr);
    }
    Enter_Queue(sendQ_ptr,buf);
}


