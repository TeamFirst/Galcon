#include "criticalmessage.h"
#include <QMessageBox>
CCriticalMessage::CCriticalMessage(QObject *parent) :
    QObject(parent)
{
}
void CCriticalMessage::Show(const QString & title, const QString & text, bool sync)
{
    QMessageBox box;
    box.setText(text);
    box.setWindowTitle(title);
    if (sync)
        box.exec();
    else
        box.show();
}
