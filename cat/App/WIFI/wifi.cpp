#include "wifi.h"
#include <QTime>
#include <QDebug>
#include <iostream>
#include "../../Base/base.h"

WIFI* WIFI::instance = nullptr;
WIFI::WIFI()
{
    //wifi遮罩
    scanBarTimer = new QTimer(this);
    scanBarTimer->setInterval(0);
    scanBarTimer->setSingleShot(true);//触发一次
    connect(scanBarTimer,SIGNAL(timeout()),this,SLOT(slot_scanOver()));
}

WIFI::~WIFI()
{
    delete scanBarTimer;
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

void WIFI::slot_scanOver(){
    mySleep(3000);
    emit sig_scanOver();
}

void WIFI::slot_scanWIFI(){
    //此处为了省力，用timer代替了线程
    scanBarTimer->start();
}