//
// Created by Samin on 2/11/18.
//

#include "AI.h"

AI::AI(GameController *controller) : gc(controller){

}

std::pair<int, int> AI::getMove() {
    return getBestCell();
}

std::pair<int, int> AI::getRandomCell() {
    auto validCells = gc->getValidCells();
    if (validCells.empty())
        return std::pair<int, int>(0, 0);

    long selectCell = rand() * validCells.size() / RAND_MAX;
    return (validCells[selectCell]);
}

std::pair<int, int> AI::getBestCell() {
    auto validCells = gc->getValidCells();
    Cell maxCell = validCells[0];
    for (auto c : validCells){
        if(gc->flips[c].size() > gc->flips[maxCell].size() )
            maxCell = c;
    }

    return (maxCell);
}

