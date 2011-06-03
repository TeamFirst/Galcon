#pragma once

#include <QDialog>

#include "message/MessageConnectToServer.h"

namespace Ui {
    class CEnterWindow;
}

class CEnterWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CEnterWindow(QWidget *parent = 0);
    ~CEnterWindow();

   void ShowWindow();
   void HideWindow();

signals:
    void SendClientToServer(Message::CMessageConnectToServerPtr);

private slots:
    void on_connectButton_clicked();

private:
    //Check connection data and send IMessage to the server if valid
    void CheckAndSend();

    Ui::CEnterWindow *ui;

}; // class CEnterWindow


