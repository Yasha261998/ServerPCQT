#ifndef MYUDP_H
#define MYUDP_H

#include <QObject>
#include <QUdpSocket>

class MyUDP : public QObject
{
    Q_OBJECT
public:
    explicit MyUDP(QObject *parent = 0);
    void SendRequest();

private:
    QUdpSocket *socket;

signals:

public slots:
    void readyRead();
};

#endif // MYUDP_H
