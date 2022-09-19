#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTcpServer>
#include <QTcpSocket>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    int serverPort = 9999;

    ui->setupUi(this);
    server = new QTcpServer(parent);
    server->listen(QHostAddress::Any,serverPort);
    connect(server,SIGNAL(newConnection()),this,SLOT(onNewConnection()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete server;
}

void MainWindow::onNewConnection()
{
    QTcpSocket *client = server->nextPendingConnection();
    connect(client,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
    connect(client,SIGNAL(disconnected()),this,SLOT(onDisconnected()));

    clients.push_back(client);
}

void MainWindow::onReadyRead()
{
    QTcpSocket *client = static_cast<QTcpSocket*>(QObject::sender());
    QByteArray data = client->readAll();

    for(QTcpSocket *client:clients)
    {
        client->write(data);
    }
}

void MainWindow::onDisconnected()
{
    QTcpSocket *client = static_cast<QTcpSocket*>(QObject::sender());
    disconnect(client,SIGNAL(disconnected()),this,SLOT(onDisconnected()));
    disconnect(client,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
    clients.removeOne(client);
}



