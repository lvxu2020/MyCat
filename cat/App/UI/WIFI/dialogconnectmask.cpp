#include "dialogconnectmask.h"
#include "ui_dialogconnectmask.h"

DialogConnectMask::DialogConnectMask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConnectMask)
{
    ui->setupUi(this);
}

DialogConnectMask::~DialogConnectMask()
{
    delete ui;
}
