//
// Created by Samin on 1/28/18.
//


#include "Client.h"

Client::Client() {
    widgetFirst = new QWidget();
    layoutFirst = new QGridLayout();
    buttonPlay = new QPushButton();
    buttonPlay-> setText("Let's Play");
    buttonExite = new QPushButton();
    buttonExite-> setText("Exit");
    layoutFirst->addWidget(buttonPlay , 0 ,0);
    layoutFirst->addWidget(buttonExite , 2 , 2);
    widgetFirst ->setLayout(layoutFirst);



    widgetFirst-> show();

    connect(buttonPlay , &QPushButton::pressed , this , &Client::gameStarting);
    connect(buttonExite , &QPushButton::pressed , widgetFirst , &QWidget::close);
}

void Client::gameStarting() {
    widgetFirst->close();
    widgetGame = new QDialog();
    layout = new QGridLayout();
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);
    layout->setMargin(-20);
    widgetGame->setFixedSize(600, 600);
    widgetGame->show();

    connect(widgetGame , &QDialog::finished , this , &Client::initialSetup);

    for(int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            gameCell[i][j] = new QPushButton();
            gameCell[i][j]->setMinimumSize(60, 60);
            gameCell[i][j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            gameCell[i][j]->setStyleSheet("border: 1px solid black");
            gameCell[i][j]->setIconSize(QSize(60, 60));

            layout->addWidget(gameCell[i][j], i, j);

            if((i == 3 && j == 3) || (i == 4 && j== 4))
                gameCell[i][j]->setIcon(QPixmap(BLACK_PIECE));
            else if((i == 4 && j== 3) || (i == 3 && j == 4))
                gameCell[i][j]->setIcon(QPixmap(WHITE_PIECE));
        }
    }


    widgetGame->setLayout(layout);

    gameController->calculateValidMoves();
    drawValidMoves();
    for(int i = 0 ; i < BOARD_SIZE ; i++){
        for(int j = 0 ; j < BOARD_SIZE ; j++){
            connect(gameCell[i][j] , &QPushButton::pressed , this , [=]() { clicked(i, j); });
        }
    }

    ai = new AI(gameController);
}

void Client::updateBoard(std::vector<std::pair<int, int>> updates) {
    for (std::pair<int, int> update : updates) {
        QPixmap icon(WHITE_PIECE);
        if (gameController->getCellData(update) == Black)
            icon = QPixmap(BLACK_PIECE);

        gameCell[update.second][update.first]->setIcon(icon);
        gameCell[update.second][update.first]->setIconSize(QSize(60, 60));
    }
}

void Client::clicked(int i, int j) {
    // HumanPlayer
    qDebug() << "Human ";
    std::vector<std::pair<int, int>> update = gameController->act(std::pair<int, int>(j, i));
    updateBoard(update);
    drawValidMoves();

    // AIPlayer
    while (gameController->currentTurn == Black) {
        qDebug() << "AI";
        update = gameController->act(ai->getMove());
        updateBoard(update);
    }

    drawValidMoves();
}

void Client::drawValidMoves() {

    for(auto c : gameController->flips){
        if(!c.second.empty()){
            gameCell[c.first.second][c.first.first]->setStyleSheet("background-color:QColor(107 , 170 , 250) ; border: 0.5px solid black");
            gameCell[c.first.second][c.first.first]->setEnabled(true);
        }
        else {
            gameCell[c.first.second][c.first.first]->setStyleSheet("background-color:QColor(107 , 170 , 150) ; border: 0.5px solid black ");
            gameCell[c.first.second][c.first.first]->setEnabled(false);
        }
    }
}

void Client::initialSetup() {
    gameController = new GameController();
    ai = new AI(gameController);
    widgetFirst->show();
}
