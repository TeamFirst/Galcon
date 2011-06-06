#include "Mainwindow.h"
#include "ui_mainwindow.h"

namespace GUI
{
   CMainWindow::CMainWindow(QWidget *parent) :
       QDialog(parent),
       ui(new Ui::CMainWindow)
   {
       ui->setupUi(this);
   }

   CMainWindow::~CMainWindow()
   {
       delete ui;
   }

   void CMainWindow::ShowWindow()
   {
      show();
   }

   void CMainWindow::DestroyWindow()
   {
      hide();
   }
}
