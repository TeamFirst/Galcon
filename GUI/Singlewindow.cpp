#include <QDebug>

#include <QVariant>

#include "Singlewindow.h"
#include "ui_singlewindow.h"

namespace GUI
{

   CSingleWindow::CSingleWindow(QWidget *parent) :
      QDialog(parent),
      ui(new Ui::CSingleWindow),
      m_validator(new QIntValidator)
   {
       ui->setupUi(this);
       for(int i = 0; i < 10; ++i)
       {
          if(i < 7)
          {
            ui->comboBoxNumberBots->addItem(QVariant(i + 1).toString());
          }
          ui->comboBoxLevelBots->addItem(QVariant(i + 1).toString());
       }

      m_validator->setBottom(1);

      ui->lineEditDispersion->setValidator(m_validator);
      ui->lineEditFleetMaxCount->setValidator(m_validator);
      ui->lineEditFleetMinCount->setValidator(m_validator);
      ui->lineEditFlySpeed->setValidator(m_validator);
      ui->lineEditGrowSpeed->setValidator(m_validator);
      ui->lineEditMapHeigt->setValidator(m_validator);
      ui->lineEditMapWidth->setValidator(m_validator);
      ui->lineEditPlanetMaxSize->setValidator(m_validator);
      ui->lineEditPlanetMinSize->setValidator(m_validator);
   }

   CSingleWindow::~CSingleWindow()
   {
      delete ui;
      delete m_validator;
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

   /// ----------------------- check input data



} // namespace GUI












