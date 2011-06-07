#include <QVariant>

#include "Singlewindow.h"
#include "ui_singlewindow.h"

namespace GUI
{

   CSingleWindow::CSingleWindow(QWidget *parent) :
       QDialog(parent),
       ui(new Ui::CSingleWindow)
   {
       ui->setupUi(this);
       for(int i = 0; i < 10; ++i)
       {
          ui->comboBoxNumberBots->addItem(QVariant(i + 1).toString());
          ui->comboBoxLevelBots->addItem(QVariant(i + 1).toString());
       }
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
      Message::CMessageConnectToSingleGamePtr mess(
               new Message::CMessageConnectToSingleGame);

      mess->m_namePlayer = ui->lineEditNamePlayer->text().toStdString();

      mess->m_mapWidth = ui->lineEditMapWidth->text().toUInt();
      mess->m_mapHeigth = ui->lineEditMapHeigt->text().toUInt();

      mess->m_flySpeed = ui->lineEditFlySpeed->text().toUInt();
      mess->m_growSpeed = ui->lineEditGrowSpeed->text().toUInt();

      mess->m_planetMinSize = ui->lineEditPlanetMinSize->text().toUInt();
      mess->m_planetMaxSize = ui->lineEditPlanetMaxSize->text().toUInt();

      mess->m_dispersionPlanets = ui->lineEditDispersion->text().toUInt();

      mess->m_fleetMinCount = ui->lineEditFleetMinCount->text().toUInt();
      mess->m_fleetMaxCount = ui->lineEditFleetMaxCount->text().toUInt();

      mess->m_botNumber = ui->comboBoxNumberBots->currentText().toUInt();
      mess->m_botLevel = ui->comboBoxLevelBots->currentText().toUInt();

      emit SendClientToSingleGame(mess);
   }

} // namespace GUI


