#pragma once
#include <QDialog>

namespace GUI
{
   class CPauseWindow : public QDialog
   {
      Q_OBJECT

   public:
      explicit CPauseWindow(QWidget* parent = 0);

   signals:
      void ReturnToGame();
      void ExitGame();

   private:
      QPushButton* returnButton;
      QPushButton* exitButton;
   };
} //Namespace GUI
