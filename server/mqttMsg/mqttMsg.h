#ifndef _MQTTMSG_H_
#define _MQTTMSG_H_

#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "MQTTClient.h"

#define CONFIG_PATH "/home/lvxu/server.conf"

typedef struct{
    int port;
    char address[128];
    char id[128];
    char topic[128];
}NetParemeter;

void * mqttMsgRec(void *p);
void * mqttMsgSend(void *p);
int opt_init(int *port, char address[], char sub_id[], char topic[]);
void delivered(void *context,MQTTClient_deliveryToken dt);
void connlost(void *context,char *cause);
int msgarrvd(void *context,char *topicName,int topicLen,MQTTClient_message *message);

#endif  //_MQTTMSG_H_
