//
// Created by Samin on 2/6/18.
//

#ifndef OTHELLO_GAMECONTROLLER_H
#define OTHELLO_GAMECONTROLLER_H

#include "Constants.h"
#include <vector>
#include <map>
#include <QDebug>

enum Side {
    Black = -1,
    White = 1
};

typedef std::pair<int, int> Cell;

class GameController {
public:
    GameController();
    bool isValidMove(Cell move);
    void calculateValidMoves();
    std::map<Cell, std::vector<Cell>> flips;
    std::vector<Cell> act(Cell cell);
    void changeCurrentTurn();

    bool areThereAnyValidMoves;
    int getCellData(Cell cell);
    Side currentTurn = White;

private:
    void calculateValidMovesForCell(int, int);
    void calculateValidMovesForCellInDirection(int, int, int, int);
    bool checkValidNextMoveOncheck(int , int , int , int);


    int gameBoard [BOARD_SIZE][BOARD_SIZE];
//    std::vector<Cell> validMoves;

};


#endif //OTHELLO_GAMECONTROLLER_H
