#ifndef WAITWINDOW_H
#define WAITWINDOW_H

#include <QDialog>
#include "../message/MessageTimeToStartGame.h"
#include <QTimer>;
namespace Ui {
    class CWaitWindow;
}

class CWaitWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CWaitWindow(QWidget *parent = 0);
    ~CWaitWindow();
public slots:
    void TakeStartGame(Message::CMessageTimeToStartGamePtr);
private slots:
    void slTimer();
private:
    unsigned int m_left;
    QTimer m_timer;
    Ui::CWaitWindow *ui;
};

#endif // WAITWINDOW_H
