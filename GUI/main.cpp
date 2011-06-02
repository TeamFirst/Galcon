#include <QApplication>
#include "gui.h"
#include "Spike.h"
#include <QObject>
int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    CSpike spike;


    return a.exec();
}
