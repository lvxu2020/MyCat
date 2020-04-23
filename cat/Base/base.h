#ifndef BASE_H
#define BASE_H

#include <QObject>
#include <QDebug>

namespace BaseSpace{
    using namespace std;
    void mySleep(int );
}
using namespace BaseSpace;
class Base : public QObject
{
    Q_OBJECT
public:
    Base();
};

#endif // BASE_H
