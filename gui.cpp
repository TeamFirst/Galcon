#include "gui.h"

CGUI::CGUI(QObject *parent) :
    QObject(parent)
{
    connect(m_enterWindow, SIGNAL(SendClientToServer(pIMessage)), this, SIGNAL(SendClientToServer(pIMessage)));
}
