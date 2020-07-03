#ifndef _REGISTER_H_
#define _REGISTER_H_

#define SEM_REQ_SHM_PATH "/"
#define SEM_REQ_SHM_CHAR 'a'
#define SEM_CGIWRITE_PATH "/bin"
#define SEM_CGIWRITE_CHAR 'b'
#define SEM_RETURNCGI_PATH "/bin"
#define SEM_RETURNCGI_CHAR 'c'
#define SHM_PATH "/bin"
#define SHM_CHAR 'd'
#define SHM_MAX 128
#define SHM_TASK_TRTURN_OK 6
#define SHM_CHECK_OK "yes"

void * registerUsr(void *p);
int semaphore_p(int semId);
int semaphore_v(int semId);
int getSemId(char *path,char ch);
int analysis(char *buf);

#endif  //_REGISTER_H_
