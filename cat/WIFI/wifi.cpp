#include "wifi.h"
#include <QTime>
#include <unistd.h>


WIFI* WIFI::instance = nullptr;
WIFI::WIFI()
{
    //wifi扫描进度条
    scanBarTimer = new QTimer(this);
    scanBarTimer->setInterval(0);
    scanBarTimer->setSingleShot(true);//触发一次
    connect(scanBarTimer,SIGNAL(timeout()),this,SLOT(slot_scanBarVelue()));
}

WIFI::~WIFI()
{
    delete instance;
}

WIFI* WIFI::getInstance(){
    static WIFI* wifi = NULL;
        if(!wifi)
        {
            wifi = new WIFI();
            instance = wifi;
        }
        return wifi;
}

void WIFI::slot_scanBarVelue(){
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    for(int i = 0;i<10;i++){
        usleep((qrand() % (10) +1 ) * 100000);
        emit sig_scanBarVelChange(qrand() % (10) + 1 + 11 * i);
    }
    emit sig_scanBarVelChange(100);
    sleep(1);
    emit sig_scanBarVelChange(0);
}

void WIFI::slot_scanWIFI(){
    //此处想异步执行5秒钟进度条动画，没开线程。使用的timer做法
    scanBarTimer->start();

}
