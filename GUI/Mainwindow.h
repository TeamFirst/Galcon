#pragma once

#include <QDialog>

namespace Ui
{
    class CMainWindow;
}

namespace GUI
{
   class CMainWindow : public QDialog
   {
       Q_OBJECT

   public:
       explicit CMainWindow(QWidget *parent = 0);
       ~CMainWindow();

      void ShowWindow();
      void DestroyWindow();

   private:
       Ui::CMainWindow *ui;

   }; // class CMainWindow

} // namespace GUI

