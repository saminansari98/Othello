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
#include "GameController.h"
#include "AI.h"
#include <QDebug>
#include <QPalette>
#include <QGridLayout>
#include <QLabel>
#include <QDialog>
#include <QStatusBar>
//#include <sys/socket.h>



class Client : public QObject {
public:
    Client();

private:
    GameController *gameController = new GameController();
    QWidget *widgetFirst;
    QDialog *widgetGame;
    QGridLayout *layoutFirst;
    QGridLayout *layout;
    QPushButton *buttonPlay;
    QPushButton *buttonExite;
    QLabel *blackScoreLabel;
    QLabel *whiteScoreLabel;
    QPushButton *gameCell[BOARD_SIZE][BOARD_SIZE];

    AI *ai;

    void gameStarting();

    void clicked(int, int);

    void updateBoard(std::vector<std::pair<int, int>>);

    void drawValidMoves();

    void initialSetup();

};


#endif //ETTELOCLIENT_CLIENT_H
