#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QUdpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;
    //QTimer *Timer;
    QLabel *ArrayLabel[9];
    QUdpSocket *socket;
signals:

public slots:
    void SendAndGet();
public:
    void MsgError(int NumError);
    void BarStatus(int msg);
    void DrawingColorLoom(char* str);
    void SendRequest();
};

#endif // MAINWINDOW_H
