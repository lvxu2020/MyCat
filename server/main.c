#include "stdio.h"
#include <pthread.h>
#include "./register/register.h"
#include "./mqttMsg/mqttMsg.h"
#include "./control/control.h"


int main()
{
    printf("server start !!!\n");
    pthread_t reg_id,ctl_id,mqtt_id;
    //注册用户
    pthread_create(&reg_id,NULL,registerUsr,NULL);
    //远程控制命令
    pthread_create(&ctl_id,NULL,remoteCmd,NULL);
    //mqtt操作
    pthread_create(&mqtt_id,NULL,mqttMsg,NULL);

    pthread_join(reg_id,NULL);
    pthread_join(ctl_id,NULL);
    pthread_join(mqtt_id,NULL);

}
