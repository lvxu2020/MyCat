#include "dialogconnectmask.h"
#include "ui_dialogconnectmask.h"
#include "../../WIFI/wifi.h"

DialogConnectMask::DialogConnectMask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConnectMask)
{
    ui->setupUi(this);
    connect(WIFI_Single::instance(),SIGNAL(sig_connectOver(bool)),this,SLOT());
}

DialogConnectMask::~DialogConnectMask()
{
    delete ui;
}
