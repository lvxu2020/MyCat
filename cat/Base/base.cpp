#include "base.h"
#include <QCoreApplication>
#include <QTime>

Base::Base()
{

}
//qt是针对于图形界面的程序，如果直接sleep，那界面势必无法响应。无法刷新。
void BaseSpace::mySleep(int ms = 1000){
    QTime time;
    time.start();
    while (time.elapsed() < ms)
    {
        QCoreApplication::processEvents();
    }
}
