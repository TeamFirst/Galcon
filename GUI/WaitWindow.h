#ifndef WAITWINDOW_H
#define WAITWINDOW_H

#include <QDialog>
#include "message/MessageTimeToStartGame.h"
#include <QTimer>
namespace Ui {
    class CWaitWindow;
}

class CWaitWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CWaitWindow(QWidget *parent = 0);
    ~CWaitWindow();

   void ShowWindow();
   void HideWindow();

   void SetSecondToStart(unsigned int second);

private slots:
    void slotIncremetTimer();

private:
    unsigned int m_secondToStart;
    QTimer m_timer;
    Ui::CWaitWindow *ui;
};

#endif // WAITWINDOW_H
