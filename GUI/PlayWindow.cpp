#include "PlayWindow.h"
#include "ui_playwindow.h"

CPlayWindow::CPlayWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CPlayWindow)
{
    ui->setupUi(this);
}

CPlayWindow::~CPlayWindow()
{
    delete ui;
}
