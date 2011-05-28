#ifndef ENTERWINDOW_H
#define ENTERWINDOW_H

#include <QWidget>

namespace Ui {
    class CEnterWindow;
}

class CEnterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CEnterWindow(QWidget *parent = 0);
    ~CEnterWindow();

private:
    Ui::CEnterWindow *ui;
};

#endif // ENTERWINDOW_H
