//
// Created by Samin on 2/6/18.
//

#include "GameController.h"

void GameController::calculateValidMoves() {

}

bool GameController::isValidMove(Cell move) {
    return std::find(validMoves.begin(), validMoves.end(), move) != validMoves.end();
}

std::vector<Cell> GameController::act(Cell cell) {
    if (false) //(!isValidMove(cell))
        return std::vector<Cell>();

    gameBoard[cell.first][cell.second] = currentTurn;
    currentTurn = (currentTurn == White ? Black : White);
    std::vector<Cell> result = { Cell(cell.first, cell.second) };
    return result;
}

int GameController::getCellData(Cell cell) {
    return gameBoard[cell.first][cell.second];
}
