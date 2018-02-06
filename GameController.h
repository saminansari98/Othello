//
// Created by Samin on 2/6/18.
//

#ifndef OTHELLO_GAMECONTROLLER_H
#define OTHELLO_GAMECONTROLLER_H

#include "constants.h"
#include <vector>

enum Side {
    Black = -1,
    White = 1
};

typedef std::pair<int, int> Cell;

class GameController {
public:
    bool isValidMove(Cell move);
    std::vector<Cell> act(Cell cell);
    int getCellData(Cell cell);

private:
    void calculateValidMoves();
    int gameBoard [BOARD_SIZE][BOARD_SIZE];
    std::vector<Cell> validMoves;
    Side currentTurn;
};


#endif //OTHELLO_GAMECONTROLLER_H
