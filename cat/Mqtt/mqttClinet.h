#ifndef MQTTCLINET_H
#define MQTTCLINET_H

#include <string>
#include "MQTTClient.h"

class MqttClinet
{
public:
    MqttClinet();
    void setInit(std::string serverAdd, std::string port, int interval, int session);
private:
    MQTTClient client;
    volatile MQTTClient_deliveryToken deliveredtoken;
    MQTTClient_connectOptions conn_opts;
    std::string addPort;
    bool isInit = false;
    int keepAliveInterval;
    int cleansession;
};

#endif // MQTTCLINET_H
