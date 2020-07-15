#include "mqttClinet.h"
#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


MqttClinet::MqttClinet()
{
    conn_opts = MQTTClient_connectOptions_initializer;
}

void MqttClinet::setInit(std::string serverAdd, std::string port, int interval, int session)
{
    addPort = "tcp://" + serverAdd + ":" + port;
    conn_opts.keepAliveInterval = interval;
    conn_opts.cleansession = session;
    isInit = true;
}
