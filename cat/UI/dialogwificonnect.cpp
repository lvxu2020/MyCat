#include "dialogwificonnect.h"
#include "ui_dialogwificonnect.h"

DialogWIFIConnect::DialogWIFIConnect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogWIFIConnect)
{
    ui->setupUi(this);
}

DialogWIFIConnect::~DialogWIFIConnect()
{
    delete ui;
}
