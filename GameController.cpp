//
// Created by Samin on 2/6/18.
//

#include <QDialog>
#include "GameController.h"

GameController::GameController() {
    currentTurn = White;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            gameBoard[i][j] = 0;

            int a = BOARD_SIZE / 2;
            int b = a - 1;

            if ((i == b && j == b) || (i == a && j == a))
                gameBoard[i][j] = Black;
            if ((i == a && j == b) || (i == b && j == a))
                gameBoard[i][j] = White;
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
    return !(flips[move].empty());
}

void GameController::printMap() {
    for (auto c : flips) {
        qDebug() << "Cell: (" << c.first.first << ", " << c.first.second << ")   :";
        qDebug() << c.second.size() << endl;
        for (Cell flip : c.second) {
//            qDebug() << "(" << flip.first << ", " << flip.second << "), ";
        }
//        qDebug() << endl << endl;
    }
}

std::vector<Cell> GameController::act(Cell cell) {
//    printMap(flips);

    std::vector<Cell> result;

    if (isValidMove(cell)) {
        gameBoard[cell.first][cell.second] = currentTurn;
        result = {Cell(cell.first, cell.second)};
        for (auto c : flips[cell]) {
            result.push_back(c);
            gameBoard[c.first][c.second] = ((currentTurn == White) ? White : Black);
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
    for (int stepX = -1; stepX < 2; stepX++) {
        for (int stepY = -1; stepY < 2; stepY++) {
            if (stepX == 0 && stepY == 0)
                continue;

            calculateValidMovesForCellInDirection(x, y, stepX, stepY);
        }
    }
}

void GameController::calculateValidMovesForCellInDirection(int x, int y, int stepX, int stepY) {

    Cell c(x, y);
    if (checkValidNextMoveOncheck(x, y, stepX, stepY)) {
        x += stepX;
        y += stepY;
    } else {
        return;
    }

    std::vector<Cell> newlyFound;
    while (gameBoard[x][y] != 0) {
        if (gameBoard[x][y] != currentTurn) {
            newlyFound.emplace_back(x, y);
        } else {
            for (Cell cell : newlyFound)
                flips[c].push_back(cell);

            return;
        }

        if (checkValidNextMoveOncheck(x, y, stepX, stepY)) {
            x += stepX;
            y += stepY;
        } else {
            return;
        }
    }
}

bool GameController::checkValidNextMoveOncheck(int x, int y, int stepX, int stepY) {
    if ((x + stepX >= 0) && (x + stepX < BOARD_SIZE)) {
        if ((y + stepY >= 0) && (y + stepY < BOARD_SIZE)) {
            return true;
        }
    }
    return false;
}

void GameController::changeCurrentTurn() {
    currentTurn = (currentTurn == White ? Black : White);
    calculateValidMoves();
}

std::vector<Cell> GameController::getValidCells() {
    std::vector<Cell> validCells;

    for (auto c : flips)
        if (!c.second.empty())
            validCells.push_back(c.first);

    return validCells;
}

void GameController::calculateWinner() {
    QDialog *winner = new QDialog();
    QGridLayout *layoutWinner = new QGridLayout();
    QLabel *lableWinner = new QLabel();

    int white = 0;
    int black = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (gameBoard[i][j] == Black)
                black++;
            else if (gameBoard[i][j] == White)
                white++;
        }
    }


    if (black > white)
        lableWinner->setText(QString("BLACK IS WINNER"));
    else if (white > black)
        lableWinner->setText(QString("WHITE IS WINNER"));
    else
        lableWinner->setText(QString("NO ONE"));

    layoutWinner->addWidget(lableWinner);
    winner->setLayout(layoutWinner);
    winner->exec();
}



