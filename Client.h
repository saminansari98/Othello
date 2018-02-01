//
// Created by Samin on 1/28/18.
//

#ifndef ETTELOCLIENT_CLIENT_H
#define ETTELOCLIENT_CLIENT_H

#include <QtNetwork/QTcpSocket>
#include <QTWidgets/QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QtWidgets/QListWidget>
//#include <sys/socket.h>



class Client : public QObject{
public:
    Client();

private:
    QTcpSocket *tcpSocket;
    QWidget *widget;
    QGridLayout *layout;
    QPushButton *buttonPlay;
    QPushButton *buttonExite;

    void gameStarting();

};


#endif //ETTELOCLIENT_CLIENT_H
