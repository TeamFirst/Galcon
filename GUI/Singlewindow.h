#pragma once

#include <QDialog>

#include "message/MessageConnectToServer.h"

namespace Ui
{
    class CSingleWindow;
}

namespace GUI
{
   class CSingleWindow : public QDialog
   {
       Q_OBJECT

   public:
      explicit CSingleWindow(QWidget *parent = 0);
      ~CSingleWindow();

      void ShowWindow();
      void DestroyWindow();

   signals:
      void SendClientToServer(Message::CMessageConnectToServerPtr);

   private slots:
      void on_pushButtonStartPlay_clicked();

   private:

       Ui::CSingleWindow *ui;

   }; // class CSingleWindow

} // namespace GUI


