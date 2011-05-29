#ifndef ENTERWINDOW_H
#define ENTERWINDOW_H

#include <QWidget>

namespace Ui {
    class CEnterWindow;
}
typedef IMessage * pIMessage;

class CEnterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CEnterWindow(QWidget *parent = 0);
    ~CEnterWindow();
signals:
    void SendClientToServer(pIMessage mess);

private:
    //Check connection data and send to the server if valid
    void CheckAndSend();
    Ui::CEnterWindow *ui;

private slots:
    void on_connectButton_clicked();
};

#endif // ENTERWINDOW_H
