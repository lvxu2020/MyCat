#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "./WIFI/wifi.h"
#include "./UI/WIFI/dialogwificonnect.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scanMask = new DialogScanMask(this);
    connect(WIFI_Single::instance(),SIGNAL(sig_scanOver()),this,SLOT(slot_scanfOver()));
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
void MainWindow::slot_scanfOver(){

    QListWidgetItem* aItem=new QListWidgetItem();
    aItem->setText(" woshi xin jian de"); //设置文字标签
    QFont font;
    font.setPointSize(18);
    aItem->setFont(font);
    aItem->setFlags(Qt::ItemIsSelectable |Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
    ui->listWIFI->addItem(aItem);
    scanMask->close();
}

void MainWindow::on_WIFIScan_clicked()
{
    emit sig_scanWIFI();

    scanMask->show();
}



void MainWindow::on_listWIFI_clicked(const QModelIndex &index)
{

    DialogWIFIConnect dialog(this);
    dialog.exec();

}
