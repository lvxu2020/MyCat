#ifndef WIFI_H
#define WIFI_H

#include "../../Base/singleton.h"
#include <QObject>
#include <QTimer>
#include "../../Base/Thread.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>


class WIFI : public QObject
{
    Q_OBJECT
public:
    void init();
    const std::vector<std::string>& getWifiNameVec() const { return mWifiNameVec; };
    void addWifiNameVec(const std::string str);
    void setConnectingWIFI(std::string str);
    std::string getConnectingWIFI( );
signals:
    void sig_scanOver(bool);
    void sig_connectOver(bool);
public slots:
    void slot_scanWIFI();
    void slot_scanOver();
private:
    WIFI();
    ~WIFI();
    QTimer* scanBarTimer = nullptr;
    std::vector<std::string> mWifiNameVec;
    std::string mConnectingWifi;
    friend class Singleton<WIFI>;
};

typedef Singleton<WIFI> WIFI_Single;    // 方便使用

#endif // WIFI_H
