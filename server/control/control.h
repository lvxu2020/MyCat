#ifndef _CONTROL_H_
#define _CONTROL_H_

#define MQ_KEY_PATH "/lib"
#define MQ_KEY_CHAR 'A'
#define MQ_MSGBUF_LEN 50

void * remoteCmd(void *p);
typedef struct mqbuf
{
        long type;
        char msg[MQ_MSGBUF_LEN];
}MSG;

int getMqId(char *path,char ch);
int processTask(MSG *p);

#endif  //_CONTROL_H_
