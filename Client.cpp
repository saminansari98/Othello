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
}

void Client::gameStarting() {
    widgetFirst->close();
    widgetGame = new QDialog();
    layout = new QGridLayout();
    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);
    layout->setMargin(-20);
    widgetGame->show();

    connect(widgetGame , &QDialog::finished , this , &Client::initialSetup);

    for(int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            gameCell[i][j] = new QPushButton();
            gameCell[i][j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            gameCell[i][j]->setMinimumWidth(60);
            gameCell[i][j]->setMinimumHeight(60);

            layout->addWidget(gameCell[i][j], i, j);
            gameCell[i][j]->setStyleSheet("border: 1px solid black");

            if(i == 3 && j == 3) {
                gameCell[i][j]->setIcon(QPixmap(BLACK_PIECE));
                gameCell[3][3]->setIconSize(QSize(60, 60));
            }
            if(i == 4 && j== 3) {
                gameCell[i][j]->setIcon(QPixmap(WHITE_PIECE));
                gameCell[4][3]->setIconSize(QSize(60, 60));
            }
            if(i == 3 && j == 4){
                gameCell[i][j]->setIcon(QPixmap(WHITE_PIECE));
                gameCell[3][4]->setIconSize(QSize(60, 60));
            }
            if(i == 4 && j== 4) {
                gameCell[i][j]->setIcon(QPixmap(BLACK_PIECE));
                gameCell[4][4]->setIconSize(QSize(60, 60));
            }

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
    // HumanPlayer
    qDebug() << "Human ";
    std::vector<std::pair<int, int>> update = gameController->act(std::pair<int, int>(j, i));
    updateBoard(update);

    // AIPlayer
    while (gameController->currentTurn == Black) {
        qDebug() << "AI";
        update = gameController->act(randomCellSelect());
        updateBoard(update);
    }

    drawValidMoves();
}

void Client::drawValidMoves() {
//    bool emptyOrNot = true;

    for(auto c : gameController->flips){
        if(!c.second.empty()){
//            emptyOrNot = false;
            gameCell[c.first.second][c.first.first]->setStyleSheet("background-color:QColor(107 , 170 , 250) ; border: 0.5px solid black");
            gameCell[c.first.second][c.first.first]->setEnabled(true);
        }
        else {
            gameCell[c.first.second][c.first.first]->setStyleSheet("background-color:QColor(107 , 170 , 150) ; border: 0.5px solid black ");
            gameCell[c.first.second][c.first.first]->setEnabled(false);
        }
    }

//    if(emptyOrNot){
//        gameController->changeCurrentTurn();
//        updateBoard(gameController->act(randomCellSelect()));
//        drawValidMoves();
//    }
}


Cell Client::randomCellSelect() {
    std::vector<Cell> validCells;

    for(auto c : gameController->flips)
        if (!c.second.empty())
            validCells.push_back(c.first);

    long selectCell = rand() * validCells.size() / RAND_MAX;
//    long selectCell = rand()%validCells.size();
    return (validCells[selectCell]);
}

void Client::initialSetup() {
    gameController = new GameController();
    widgetFirst->show();
}
