//
// Created by Samin on 1/28/18.
//


#include "Client.h"

Client::Client() {
    widget = new QWidget();
    layout = new QGridLayout();
    buttonPlay = new QPushButton();
    buttonPlay-> setText("Let's Play");
    buttonExite = new QPushButton();
    buttonExite-> setText("Exite");
    layout->addWidget(buttonPlay , 0 ,0);
    layout->addWidget(buttonExite , 2 , 2);
    widget ->setLayout(layout);

    tcpSocket = new QTcpSocket() ;
    tcpSocket ->  connectToHost ("127.0.0.1" , 8000) ;

    widget-> show();

    connect(buttonPlay , &QPushButton::pressed , this , &Client::gameStarting);

}

void Client::gameStarting() {
    widget->close();
    widget = new QWidget();
    layout = new QGridLayout();
    widget->show();


}
