#ifndef WIFI_H
#define WIFI_H

#include <QObject>
#include <QTimer>
class WIFI : public QObject
{
    Q_OBJECT
public:
    static WIFI* instance;
    static WIFI* getInstance();
    WIFI();
    ~WIFI();

signals:
    void sig_scanBarVelChange(int);
public slots:
    void slot_scanWIFI();
    void slot_scanBarVelue();
private:
    QTimer* scanBarTimer = nullptr;
};

#endif // WIFI_H
