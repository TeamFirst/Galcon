#ifndef GUI_H
#define GUI_H

#include <QObject>
class QHostAddress;
class QString;
class IMessage;
class CGUI : public QObject
{
    Q_OBJECT
public:
    explicit CGUI(QObject *parent = 0);

signals:
    void SignalInWaitFor(quint8);
    void SignalOutConnectToHost(QHostAddress host, quint32 port, QString name);

public slots:
    void SlotServerError(IMessage );

};

#endif // GUI_H
