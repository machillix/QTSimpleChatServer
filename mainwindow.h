#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTcpServer;
class QTcpSocket;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();

private:
    Ui::MainWindow *ui;
    QTcpServer *server;
    QList<QTcpSocket*> clients;
};
#endif // MAINWINDOW_H
