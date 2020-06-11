#include "mainwindow.h"

#include <QApplication>
#include "../LOG/LogStore.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LogStore log;

    MainWindow w;
    w.show();
    log.start();
    log.detach();


    return a.exec();
}
