#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QDialog>
#include <QGraphicsScene>

#include <QVector>
#include "GUIView.h"
#include "message/MessageStartMapGame.h"
#include "GUIFleet.h"

class QGraphicsScene;
class CPlayArea;
class CPlanet;
class CFleet;


namespace Ui {
    class CPlayWindow;
}

class CPlayWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CPlayWindow(QWidget *parent = 0);
    ~CPlayWindow();
    CGUIView * GetView();
public slots:
    void TakeFieldSize(unsigned int X, unsigned int Y);
private slots:
    void UpdateFleets();
    void slGameStarts();
    void slUpdate();
private:
    void DrawSky();


    QVector<CGUIFleet *> m_gFleets;
    const std::vector<CPlanet *> * m_planets;
    const std::list<CFleet* > * m_fleets;
    QGraphicsScene m_scene;
    CPlayArea * m_playArea;
    CGUIView m_view;
    void SetNewPlaySize();
    double m_horLogic;
    double m_verLogic;

    double m_horPhys;
    double m_verPhys;

    // size relations between logical and physical coordinates
    double m_k;

    Ui::CPlayWindow *ui;
};

#endif // PLAYWINDOW_H
