#include "Singlewindow.h"
#include "ui_singlewindow.h"

namespace GUI
{

   CSingleWindow::CSingleWindow(QWidget *parent) :
       QDialog(parent),
       ui(new Ui::CSingleWindow)
   {
       ui->setupUi(this);
   }

   CSingleWindow::~CSingleWindow()
   {
       delete ui;
   }

   void CSingleWindow::ShowWindow()
   {
      show();
   }

   void CSingleWindow::DestroyWindow()
   {
      hide();
   }

   void CSingleWindow::on_pushButtonStartPlay_clicked()
   {
      Message::CMessageConnectToSingleGamePtr mess(new Message::CMessageConnectToSingleGame);
      emit SendClientToSingleGame(mess);
   }

} // namespace GUI


