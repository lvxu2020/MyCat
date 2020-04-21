#ifndef WIFI_H
#define WIFI_H

#include "../../Base/singleton.h"
#include <QObject>
#include <QTimer>

class WIFI : public QObject
{
    Q_OBJECT
public:

signals:
    void sig_scanOver();
public slots:
    void slot_scanWIFI();
    void slot_scanOver();
private:
    WIFI();
    ~WIFI();
    QTimer* scanBarTimer = nullptr;
    friend class Singleton<WIFI>;
};

typedef Singleton<WIFI> WIFI_Single;    // 方便使用

#endif // WIFI_H
