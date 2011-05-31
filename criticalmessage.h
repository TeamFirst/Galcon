#ifndef CRITICALMESSAGE_H
#define CRITICALMESSAGE_H

#include <QObject>

class CCriticalMessage : public QObject
{
    Q_OBJECT
public:
    explicit CCriticalMessage(QObject *parent = 0);
    static void Show(QString & title, QString & text, bool sync = true);

signals:

public slots:

};

#endif // CRITICALMESSAGE_H
