#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(connectServer()));
    this->connect(ui->startButton, SIGNAL(clicked()), this,SLOT(startTcpserver()));
    this->connect(ui->sendButton, SIGNAL(clicked()), this,SLOT(sendMessage()));

    ui->lineEdit->setEnabled(false);
    ui->sendButton->setEnabled(false);

    ui->textEdit->clear();
    ui->textEdit->append("Initialized...");
    isServer = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectServer()
{
    ui->startButton->setEnabled(false);
    ui->lineEdit->setEnabled(true);
    ui->sendButton->setEnabled(true);

    socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1", 19999);

    ui->textEdit->append("connect to 127.0.0.1:19999");
    connect(socket, SIGNAL(readyRead()), this, SLOT(readMessage()));

    isServer = 0;
}

void MainWindow::startTcpserver()
{
    ui->connectButton->setEnabled(false);
    ui->lineEdit->setEnabled(true);
    ui->sendButton->setEnabled(true);

    server = new QTcpServer(this);
    server ->listen(QHostAddress::Any, 19999);

    ui->textEdit->append("start server 127.0.0.1:19999");
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnect()));

    isServer =1;
}

void MainWindow::newConnect()
{
    socket = server->nextPendingConnection();
    ui->textEdit->append("connected");
    connect(socket,SIGNAL(readyRead()), this, SLOT(readMessage()));
}

void MainWindow::readMessage()
{
    QByteArray data = socket->readAll();
    qDebug()<< data;
    QString ss =  QVariant(data).toString();
    ui->textEdit->append(ss);
}

void MainWindow::sendMessage()
{
    QString strMesg=  ui->lineEdit->text();
    qDebug()<<strMesg;
    socket->write(strMesg.toStdString().c_str(),strlen(strMesg.toStdString().c_str()));

     ui->lineEdit->clear();
}
