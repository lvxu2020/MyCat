#ifndef _MQTTMSG_H_
#define _MQTTMSG_H_

#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>
#include "MQTTClient.h"
#include "../base/myQueue.h"
#include "../base/pool.h"

#define CONFIG_PATH "/home/lvxu/server.conf"
#define REC_BUF_MAX 128
#define C_TO_S_HEAD "cTos:"
#define WORK_PTAH_HEAD "/home/lvxu/usr/"
#define USER_CONF_PATH "/home/lvxu/usr"
#define STATUS "status"
#define POOL_PTH_MIN 3
#define POOL_PTH_MAX 100
#define POOL_QUEUE_MAX 100

typedef struct {
    int F_id; //负值
    char buf[20];//板子的唯一id
} regReq;

typedef struct{
    int port;
    char address[128];
    char id[128];
    char topic[128];
} NetParemeter;

typedef struct{
    int arr_N;
    int id;
    int type;
    void * (*fun)(void *);
    char buf[REC_BUF_MAX];

} DataFromClient;


typedef struct {
    bool busy;
    DataFromClient parm;
} parmElement;


void * mqttMsgRec(void *p);
void * mqttMsgSend(void *p);
int opt_init(int *port, char address[], char sub_id[], char topic[]);
void getID(char *time);
void delivered(void *context,MQTTClient_deliveryToken dt);
void connlost(void *context,char *cause);
int msgarrvd(void *context,char *topicName,int topicLen,MQTTClient_message *message);
bool getPubTask(myQueue *sendQ_ptr,qData *out);
void pushTaskPool(char *data);
bool analysisTask(DataFromClient *task,char *data);
void *statusUpdate(void *arg);
bool getParmPtr(parmElement *arr, DataFromClient **p, int max);
void freeParmPtr( parmElement *arr, int arr_N);
void *functionVec( void *p);

#endif  //_MQTTMSG_H_
