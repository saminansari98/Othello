//
// Created by Samin on 2/6/18.
//

#include <QDialog>
#include "GameController.h"

GameController::GameController() {
    for(int i = 0 ; i < 7 ; i++){
        for(int j = 0 ; j < 7 ; j++){
            gameBoard[i][j] = 0;

            if(i == 3 && j == 3) {
                gameBoard[i][j]=Black;
            }
            if(i == 4 && j== 3) {
                gameBoard[i][j]=White;
            }
            if(i == 3 && j == 4){
                gameBoard[i][j]=White;
            }
            if(i == 4 && j== 4) {
                gameBoard[i][j]=Black;
            }
        }
    }
}

void GameController::calculateValidMoves() {
    areThereAnyValidMoves = false;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            flips[Cell(i, j)] = std::vector<Cell>();

            if (gameBoard[i][j] == 0) {
                calculateValidMovesForCell(i, j);
                if (!flips[Cell(i, j)].empty())
                    areThereAnyValidMoves = true;
            }
        }
    }
}

bool GameController::isValidMove(Cell move) {
    return !flips[move].empty();
}

void printMap(std::map<Cell, std::vector<Cell>> map) {
    for (auto c : map) {
//        qDebug() << "Cell: (" << c.first.first << ", " << c.first.second << ")" << endl;
//        qDebug() << c.second.size();
        for (Cell flip : c.second) {
//            qDebug() << "(" << flip.first << ", " << flip.second << "), ";
        }
//        qDebug() << endl << endl;
    }
}

std::vector<Cell> GameController::act(Cell cell) {
//    printMap(flips);

    std::vector<Cell> result;

    if(isValidMove(cell)) {
        gameBoard[cell.first][cell.second] = currentTurn;
        result = {Cell(cell.first, cell.second)};
        for(auto c : flips[cell]) {
            result.push_back(c);
            gameBoard[c.first][c.second] *= -1;
        }


        changeCurrentTurn();
        if (!areThereAnyValidMoves) {
            changeCurrentTurn();
            if (!areThereAnyValidMoves) {
                currentTurn = Finished;
                calculateWinner();
            }
        }
    }

    return result;
}

int GameController::getCellData(Cell cell) {
    return gameBoard[cell.first][cell.second];
}

void GameController::calculateValidMovesForCell(int x, int y) {
    for(int stepX = -1 ; stepX < 2 ; stepX++){
        for(int stepY = -1 ; stepY < 2 ; stepY++){
            if(stepX == 0 && stepY == 0)
                continue;

            calculateValidMovesForCellInDirection(x, y, stepX, stepY);
        }
    }
}

void GameController::calculateValidMovesForCellInDirection(int x, int y, int stepX, int stepY) {

    Cell c(x, y);
    if(checkValidNextMoveOncheck(x , y , stepX , stepY)){
        x += stepX; y += stepY;
    }else{
        return;
    }

    std::vector<Cell> newlyFound;
    while(gameBoard[x][y] != 0) {
        if (gameBoard[x][y] == -1 * currentTurn) {
            newlyFound.emplace_back(x, y);
        }
        else {
            for (Cell cell : newlyFound)
                flips[c].push_back(cell);

            return;
        }

        if(checkValidNextMoveOncheck(x , y , stepX , stepY)){
            x += stepX; y +=stepY;
        }else{
            return;
        }
    }
}

bool GameController::checkValidNextMoveOncheck(int x , int y, int stepX , int stepY) {
    return (x + stepX  >= 0 ) && (x + stepX <= 7) && (y + stepY >= 0) && (y + stepY <= 7);
}

void GameController::changeCurrentTurn() {
    currentTurn = (currentTurn == White ? Black : White);
    calculateValidMoves();
}

std::vector<Cell> GameController::getValidCells() {
    std::vector<Cell> validCells;

    for(auto c : flips)
        if (!c.second.empty())
            validCells.push_back(c.first);

    return validCells;
}

void GameController::calculateWinner() {
    QDialog *winner = new QDialog();
    QGridLayout *layoutWinner = new QGridLayout();
    QLabel *lableWinner = new QLabel();

    int white = 0 ; int black = 0;
    for(int i = 0 ; i < BOARD_SIZE ; i++){
        for(int j = 0 ; j < BOARD_SIZE ; j++){
            if(gameBoard[i][j] == Black)
                black++;
            else if(gameBoard[i][j] == White)
                white++;
        }
    }


    if(black > white)
        lableWinner->setText(QString("BLACK IS WINNER"));
    else if(white > black)
        lableWinner->setText(QString("WHITE IS WINNER"));
    else
        lableWinner->setText(QString("NO ONE"));

    layoutWinner->addWidget(lableWinner);
    winner->setLayout(layoutWinner);
    winner->exec();
}



