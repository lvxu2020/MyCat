#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../WIFI/wifi.h"
#include "../UI/dialogwificonnect.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(WIFI::getInstance(),SIGNAL(sig_scanBarVelChange(int)),this,SLOT(slot_scanBarVelChanged(int)));
    connect(this,SIGNAL(sig_scanWIFI()),WIFI::getInstance(),SLOT(slot_scanWIFI()));

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    //主页面左上角版本信息
    ui->labVersonNum->setText("1.2.3");
    //主页面中间工作部分
    //WIFI tab页
    //WIFI链接状态
    ui->WIFIConnect->setText("未链接");
    ui->WIFIName->setText("");
    //WIFI扫描进度条
    ui->scanWIFIBar->hide();
    ui->scanWIFIBar->setValue(0);


}
void MainWindow::slot_scanBarVelChanged(int vel){
    if(vel == 0){
        ui->scanWIFIBar->hide();
    }
    ui->scanWIFIBar->setValue(vel);
}

void MainWindow::on_WIFIScan_clicked()
{
    ui->scanWIFIBar->show();
    emit sig_scanWIFI();
}



void MainWindow::on_listWIFI_clicked(const QModelIndex &index)
{
    DialogWIFIConnect dialog(this);
    dialog.exec();
}
