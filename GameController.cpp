//
// Created by Samin on 2/6/18.
//

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

}

//bool GameController::isValidMove(Cell move) {
//    return std::find(validMoves.begin(), validMoves.end(), move) != validMoves.end();
//}

std::vector<Cell> GameController::act(Cell cell) {
//    if (false) //(!isValidMove(cell))
//        return std::vector<Cell>();

    gameBoard[cell.first][cell.second] = currentTurn;
    std::vector<Cell> result = { Cell(cell.first, cell.second) };
    currentTurn = (currentTurn == White ? Black : White);
    return result;
}

int GameController::getCellData(Cell cell) {
    return gameBoard[cell.first][cell.second];
}

bool GameController::checkHasValidMoves(int x , int y) {
    if(gameBoard[x][y] !=0)
        return false;

    for(int stepX = -1 ; stepX < 2 ; stepX++){
        for(int stepY = -1 ; stepY < 2 ; stepY++){
            if(stepX == 0 && stepY == 0)
                continue;

            if(checkHasValidMovesInDirection(x , y , stepX , stepY))
                return true;
        }
    }
    return false;
}

bool GameController::checkHasValidMovesInDirection(int x , int y , int stepX , int stepY) {
    if(checkValidNextMoveOncheck(x , y , stepX , stepY)){
        x += x *stepX; y += y*stepY;
    }else{
        return false;
    }


    bool checkWhile = false;
    while(gameBoard[x][y] != 0) {
        if (!checkWhile && gameBoard[x][y] == currentTurn)
            return false;
        if (!checkWhile && gameBoard[x][y] == -1*currentTurn)
            checkWhile = true;
        if (checkWhile && gameBoard[x][y] == currentTurn)
            return true;

        if(checkValidNextMoveOncheck(x , y , stepX , stepY)){
            x += x *stepX; y += y*stepY;
        }else{
            return false;
        }
    }

    return false;
}

bool GameController::checkValidNextMoveOncheck(int x , int y, int stepX , int stepY) {
    if( ((x+1)*stepX) != -1 || ((x+1)*stepX) != 8)
        if(((y+1)*stepY) != -1 || ((y+1)*stepY) != 8)
            return true;

    return false;
}




