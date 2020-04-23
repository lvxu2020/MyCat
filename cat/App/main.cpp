#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    MainWindow w;
    w.show();
    return a.exec();
}
