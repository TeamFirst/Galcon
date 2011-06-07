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

   void GUI::CSingleWindow::on_pushButtonStartPlay_clicked()
   {
      Message::CMessageConnectToServerPtr mess(new Message::CMessageConnectToServer());
      mess->m_namePlayer = "user";
      mess->m_serverIP = "";
      mess->m_serverPort = 0;
      emit SendClientToServer(mess);
   }

} // namespace GUI


