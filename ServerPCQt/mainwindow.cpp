//Проценко Я.В.
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtGui>
#include <string>
#include <iostream>

using namespace std;

#define SERVER_PORT     50000   //server port #
#define ASK             "?"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ArrayLabel[0] = ui->label_1;
    ArrayLabel[1] = ui->label_2;
    ArrayLabel[2] = ui->label_3;
    ArrayLabel[3] = ui->label_4;
    ArrayLabel[4] = ui->label_5;
    ArrayLabel[5] = ui->label_6;
    ArrayLabel[6] = ui->label_7;
    ArrayLabel[7] = ui->label_8;
    ArrayLabel[8] = ui->label_9;

    socket = new QUdpSocket();
    bool rc = socket->bind(QHostAddress::Any, SERVER_PORT);
    if (!rc)
        cerr << "Error bind!" << endl;
    connect(socket, SIGNAL(readyRead()), this, SLOT(SendAndGet()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete socket;
}

void MainWindow::DrawingColorLoom(char* str)
{
    int number = atoi(str);
    int number2 = number/100;
    QString COLOR;
    if (str[3] == '1')
        COLOR = "rgb(255, 0, 0)";
    else
        COLOR = "rgb(68, 204, 0)";
    switch (number2)
    {
        case 17:
        {
            ui->label_1->setStyleSheet("QLabel {background-color : "+ COLOR +"; }");
            break;
        }
        case 16:
        {
            ui->label_2->setStyleSheet("QLabel {background-color : "+ COLOR +"; }");
            break;
        }
        case 15:
        {
            ui->label_3->setStyleSheet("QLabel {background-color : "+ COLOR +"; }");
            break;
        }
        default:
        {
            if (((number2-20) > 0)&&((number2-20) <= 6))
                ArrayLabel[(number2-20)+2]->setStyleSheet("QLabel {background-color : "+ COLOR +" }");
        }
    }
}

void MainWindow::BarStatus(int msg)
{
    switch(msg)
    {
    case 1:
    {
        ui->statusBar->showMessage("Отправка запроса...");
        break;
    }
    case 2:
    {
        ui->statusBar->showMessage("Данные обновлены",5000);
        break;
    }
    }
}

void MainWindow::SendRequest()
{
    cerr << "Send request" << endl;

    socket->writeDatagram(ASK, QHostAddress("192.168.0.105"), 500);
    BarStatus(1);
}

void MainWindow::on_pushButton_clicked()
{
    SendRequest();
}

void MainWindow::MsgError(int NumError)
{
    switch(NumError)
    {
    case 1:
    {
        QMessageBox::critical(this, "Ошибка", "Ошибка получения сообщения");
        break;
    }
    case 2:
    {
        QMessageBox::critical(this, "Ошибка", "Не удалось отправить ответ");
        break;
    }
    }
}
void MainWindow::SendAndGet()
{
    char Buffer[10];

    cerr << "Read" << endl;

    QHostAddress sender;
    quint16 senderPort;
    int readS = socket->readDatagram(Buffer,sizeof(Buffer),&sender,&senderPort);
    if (readS < 0)
    {
        MsgError(1);
        cerr << "Error read" << endl;
    }
    else
        cout << "Msg: " << Buffer << endl;

    int writeS = socket->writeDatagram(Buffer,QHostAddress("192.168.0.105"), 500);
    if (writeS < 0)
    {
        MsgError(2);
        cerr << "Error send" << endl;
    }

    BarStatus(2);
    DrawingColorLoom(Buffer);
}
