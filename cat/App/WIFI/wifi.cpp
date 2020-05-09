#include "wifi.h"

#include <QTime>
#include <QDebug>
#include <string.h>
#include <chrono>
#include <thread>
#include <fstream>
#include <unistd.h>

#include "../../Base/base.h"

#define SCAN_WIFI_NAME "/home/debian/Cat/wifi.txt"
#define TEST_STR "111111111      2222222222222222  333333333333 44444444"

WIFI::WIFI()
{
    //wifi遮罩
    scanBarTimer = new QTimer(this);
    scanBarTimer->setInterval(0);
    scanBarTimer->setSingleShot(true);//触发一次
    connect(scanBarTimer,SIGNAL(timeout()),this,SLOT(slot_scanOver()));
    mWifiNameVec.reserve(100);
    init();

}

void WIFI::init()
{
    system("rm /var/run/wpa_supplicant/wlan0");
    system(" wpa_supplicant -i wlan0 -c /etc/wpa_supplicant/wpa_supplicant.conf -B ");
    system(" ifconfig wlan0 up ");
}

WIFI::~WIFI()
{
    mWifiNameVec.clear();
    delete scanBarTimer;
}



void WIFI::slot_scanOver(){

    mWifiNameVec.clear();
    bool result = true;
    std::fstream fileStream;
    string file(SCAN_WIFI_NAME);
    for(bool flag = true;flag;flag = !flag){
        // 判断文件是否存在
        if(access(file.c_str(), F_OK) != 0) {
            DEBUG_E("%s not exist \n",SCAN_WIFI_NAME);
            result = false;
            break;
        }
        // 打开文件
        fileStream.open(file.c_str(), std::fstream::in);
        if(!fileStream.is_open()) {
            DEBUG_E("%s open failed\n",SCAN_WIFI_NAME);
            result = false;
            break;
        }
        std::string data,send;
        bool first = true;
        while(!(fileStream.peek() == EOF)){
            std::getline(fileStream, data);
            if(first){
                first = false;
                continue;
            }
            send = data.substr(data.find_last_of("'\t'")+1);
            addWifiNameVec(send);
        }
        fileStream.close();
    }
    emit sig_scanOver(result);
}


void WIFI::slot_scanWIFI(){

    //此处为了省力，用timer代替了线程
    system(" wpa_cli -iwlan0 scan ");
    system(" wpa_cli -iwlan0 scan_results > /home/debian/Cat/wifi.txt ");
    scanBarTimer->start();

}

void WIFI::addWifiNameVec(const std::string str)
{
    mWifiNameVec.emplace_back(str);
}

void WIFI::setConnectingWIFI(std::string str)
{
    mConnectingWifi = str;
}

std::string WIFI::getConnectingWIFI()
{
    return mConnectingWifi;
}
