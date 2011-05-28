#include "enterwindow.h"
#include "ui_enterwindow.h"

CEnterWindow::CEnterWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CEnterWindow)
{
    ui->setupUi(this);
}

CEnterWindow::~CEnterWindow()
{
    delete ui;
}
