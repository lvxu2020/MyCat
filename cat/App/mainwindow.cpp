#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "./WIFI/wifi.h"
#include "./UI/WIFI/dialogwificonnect.h"
#include <QDebug>
#include <vector>
#include "../Base/base.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scanMask = new DialogScanMask(this);
    connect(WIFI_Single::instance(),SIGNAL(sig_scanOver(bool)),this,SLOT(slot_scanfOver(bool)));
    connect(this,SIGNAL(sig_scanWIFI()),WIFI_Single::instance(),SLOT(slot_scanWIFI()));

    init();
}

MainWindow::~MainWindow()
{
    delete scanMask;
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
}
void MainWindow:: clearQListWidget(QListWidget * ptr ,QList<QListWidgetItem*> & vec){
    if(ptr == nullptr || vec.size() == 0){
        return;
    }
    for(auto it = vec.begin();it !=vec.end();it++){
        ptr->removeItemWidget(*it);
    }
    qDeleteAll(vec.begin(), vec.end());
    vec.clear();
}

void MainWindow::slot_scanfOver( bool result){

    if(!result){
        mySleep(1000);
        scanMask->close();
        return;
    }
    clearQListWidget(ui->listWIFI,lstItem);
    for(auto it = lstItem.begin();it !=lstItem.end();it++){
        ui->listWIFI->removeItemWidget(*it);
    }
    qDeleteAll(lstItem.begin(), lstItem.end());
    lstItem.clear();
    for(auto val : WIFI_Single::instance()->getWifiNameVec()){
        QListWidgetItem* pItem=new QListWidgetItem();
        lstItem.push_back(pItem);
        pItem->setText(QString::fromStdString(val));//设置文字标签
        QFont font;
        font.setPointSize(18);
        pItem->setFont(font);
        pItem->setFlags(Qt::ItemIsSelectable |Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
        ui->listWIFI->addItem(pItem);
    }
    mySleep(1000);
    scanMask->close();

}

void MainWindow::on_WIFIScan_clicked()
{
    emit sig_scanWIFI();

    scanMask->show();
}



void MainWindow::on_listWIFI_clicked(const QModelIndex &index)
{
    WIFI_Single::instance()->setConnectingWIFI(ui->listWIFI->currentItem()->text().toStdString());
    DialogWIFIConnect dialog(this);
    dialog.exec();

}
