#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QDialog>

namespace Ui {
    class CPlayWindow;
}

class CPlayWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CPlayWindow(QWidget *parent = 0);
    ~CPlayWindow();

private:
    Ui::CPlayWindow *ui;
};

#endif // PLAYWINDOW_H
