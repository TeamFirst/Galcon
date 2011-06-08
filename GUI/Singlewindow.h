#pragma once

#include <QDialog>
#include <QValidator>

#include "message/MessageConnectToSingleGame.h"

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
      void SendClientToSingleGame(const Message::CMessageConnectToSingleGamePtr mess);

   private slots:
      void on_pushButtonStartPlay_clicked();

   private:

      Ui::CSingleWindow *ui;

      QIntValidator* m_validator;

   }; // class CSingleWindow

} // namespace GUI


