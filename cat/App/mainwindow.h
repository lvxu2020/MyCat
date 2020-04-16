#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./UI/WIFI/dialogscanmask.h"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void sig_scanWIFI();
private slots:
    void slot_scanfOver();

    void on_WIFIScan_clicked();



    void on_listWIFI_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    DialogScanMask *scanMask;
    void init();
};
#endif // MAINWINDOW_H
