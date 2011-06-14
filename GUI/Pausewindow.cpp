#include "Pausewindow.h"

#include<QPushButton>
namespace GUI
{
   CPauseWindow::CPauseWindow(QWidget *parent) : QDialog(parent)
   {
      returnButton = new QPushButton("Return to game", this);
      returnButton->setGeometry(30, 30, 200, 50);
      connect(returnButton, SIGNAL(clicked()), this, SIGNAL(ReturnToGame()));

      exitButton = new QPushButton("Exit to main menu", this);
      exitButton->setGeometry(30, 110, 200, 50);
      connect(exitButton, SIGNAL(clicked()), this, SIGNAL(ExitGame()));
   }
} //Namespace GUI

