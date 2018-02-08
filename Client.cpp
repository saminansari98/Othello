//
// Created by Samin on 1/28/18.
//


#include "Client.h"

Client::Client() {
    widgetFirst = new QWidget();
    layout = new QGridLayout();
    buttonPlay = new QPushButton();
    buttonPlay-> setText("Let's Play");
    buttonExite = new QPushButton();
    buttonExite-> setText("Exite");
    layout->addWidget(buttonPlay , 0 ,0);
    layout->addWidget(buttonExite , 2 , 2);
    widgetFirst ->setLayout(layout);



    widgetFirst-> show();

    connect(buttonPlay , &QPushButton::pressed , this , &Client::gameStarting);

}

void Client::gameStarting() {
    widgetFirst->close();
    widgetFirst = new QWidget();
    layout = new QGridLayout();
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);
    layout->setMargin(-10);
    widgetFirst->show();

    for(int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            gameCell[i][j] = new QPushButton();
            gameCell[i][j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            layout->addWidget(gameCell[i][j], i, j);

            if(i == 3 && j == 3) {
                gameCell[i][j]->setIcon(QPixmap(BLACK_PIECE));
            }
            if(i == 4 && j== 3) {
                gameCell[i][j]->setIcon(QPixmap(WHITE_PIECE));
            }
            if(i == 3 && j == 4){
                gameCell[i][j]->setIcon(QPixmap(WHITE_PIECE));
            }
            if(i == 4 && j== 4) {
                gameCell[i][j]->setIcon(QPixmap(BLACK_PIECE));
            }

        }
    }


    widgetFirst->setLayout(layout);

    drawValidMoves();
    for(int i = 0 ; i < BOARD_SIZE ; i++){
        for(int j = 0 ; j < BOARD_SIZE ; j++){
            connect(gameCell[i][j] , &QPushButton::pressed , this , [=]() { clicked(i, j); });
        }
    }
}

void Client::updateBoard(std::vector<std::pair<int, int>> updates) {
    for (std::pair<int, int> update : updates) {
        QPixmap icon(WHITE_PIECE);
        if (gameController->getCellData(update) == Black)
            icon = QPixmap(BLACK_PIECE);

        gameCell[update.second][update.first]->setIcon(icon);
        gameCell[update.second][update.first]->setIconSize(QSize(75, 75));
    }
}

void Client::clicked(int i, int j) {
//    qDebug() << j << ", " << i;
    std::vector<std::pair<int, int>> update = gameController->act(std::pair<int, int>(j, i));
    updateBoard(update);
    drawValidMoves();
}

void Client::drawValidMoves() {
    gameController->calculateValidMoves();

    for(auto c : gameController->flips){
        if(!c.second.empty()){
            gameCell[c.first.second][c.first.first]->setStyleSheet("background-color:black;");
            gameCell[c.first.second][c.first.first]->setEnabled(true);
        }
        else {
            gameCell[c.first.second][c.first.first]->setStyleSheet("background-color:white;");
            gameCell[c.first.second][c.first.first]->setEnabled(false);
        }
    }
}
