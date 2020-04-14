#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void slot_scanBarVelChanged(int);


    void on_WIFIScan_clicked();



    void on_listWIFI_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    void init();
};
#endif // MAINWINDOW_H
