#ifndef DIALOGWIFICONNECT_H
#define DIALOGWIFICONNECT_H

#include <QDialog>

namespace Ui {
class DialogWIFIConnect;
}

class DialogWIFIConnect : public QDialog
{
    Q_OBJECT

public:
    explicit DialogWIFIConnect(QWidget *parent = nullptr);
    ~DialogWIFIConnect();

private:
    Ui::DialogWIFIConnect *ui;
};

#endif // DIALOGWIFICONNECT_H
