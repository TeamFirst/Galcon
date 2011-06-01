#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QDialog>
#include "message/MessageStartMapGame.h"
namespace Ui {
    class CPlayWindow;
}

class CPlayWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CPlayWindow(QWidget *parent = 0);
    ~CPlayWindow();
public slots:
    void TakeStartGame(Message::CMessageStartMapGamePtr mess);

private:
    void SetNewPlaySize();
    double m_horLogic;
    double m_verLogic;

    double m_horPhys;
    double m_verPhys;
    // size relations between logical and physical coordinates
    double m_k;
    Ui::CPlayWindow *ui;
};

#endif // PLAYWINDOW_H
