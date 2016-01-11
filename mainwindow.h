#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void startTcpserver();
    void newConnect();
    void connectServer();
    void sendMessage();
    void readMessage();

private:
    Ui::MainWindow *ui;
    QTcpServer *server;
    QTcpSocket *socket;
    int isServer;
};

#endif // MAINWINDOW_H
