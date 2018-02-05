//
// Created by Samin on 1/28/18.
//

#ifndef ETTELOCLIENT_CLIENT_H
#define ETTELOCLIENT_CLIENT_H

#include <QTWidgets/QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QtWidgets/QListWidget>
#include <QTableWidget>
#include <QHeaderView>
#include "Constants.h"
//#include <sys/socket.h>



class Client : public QObject{
public:
    Client();

private:

    QWidget *widgetFirst;
    QGridLayout *layout;
    QPushButton *buttonPlay;
    QPushButton *buttonExite;

    QTableWidget *tableWidget;

    QPushButton *gameCell[BOARD_SIZE][BOARD_SIZE];
    void gameStarting();

};


#endif //ETTELOCLIENT_CLIENT_H
