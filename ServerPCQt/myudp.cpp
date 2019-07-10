#include "myudp.h"
#include "mainwindow.h"
#include <iostream>

using namespace std;

#define SERVER_PORT     54000   //server port #
#define ASK             "?"

MyUDP::MyUDP(QObject *parent) :
    QObject(parent)
{
    socket = new QUdpSocket(this);

    cerr << "Init socket" << endl;

    //We need to bind the UDP socket to an address and a port
    socket->bind(QHostAddress::LocalHost,SERVER_PORT);         //ex. Address localhost, port 54000
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void MyUDP::SendRequest()
{
    cerr << "Send request" << endl;

    socket->writeDatagram(ASK, QHostAddress("192.168.0.105"), 500);
    MainWindow CallFunc;
    CallFunc.BarStatus(1);
}

void MyUDP::readyRead()
{
    char Buffer[10];

    cerr << "Read" << endl;

    MainWindow CallFunc;
    QHostAddress sender;
    quint16 senderPort;
    int readS = socket->readDatagram(Buffer,sizeof(Buffer),&sender,&senderPort);
    if (readS < 0)
    {
        CallFunc.MsgError(1);
        cerr << "Error read" << endl;
    }
    else
        cout << "Msg: " << Buffer << endl;
    int writeS = socket->writeDatagram(Buffer,QHostAddress("192.168.0.105"), 500);
    if (writeS < 0)
    {
        CallFunc.MsgError(2);
        cerr << "Error send" << endl;
    }

    CallFunc.BarStatus(2);
    CallFunc.DrawingColorLoom(Buffer);
}
