#ifndef ENTERWINDOW_H
#define ENTERWINDOW_H

#include <QWidget>
#include "Message.h"
#include "messageconnecttoserver.h"

namespace Ui {
    class CEnterWindow;
}


class CEnterWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CEnterWindow(QWidget *parent = 0);
    ~CEnterWindow();

signals:
    void SendClientToServer(pIMessage mess);

private:
    //Check connection data and send IMessage to the server if valid
    void CheckAndSend();
    Ui::CEnterWindow *ui;

private slots:
    void on_connectButton_clicked();
};

#endif // ENTERWINDOW_H
