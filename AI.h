//
// Created by Samin on 2/11/18.
//

#ifndef OTHELLO_AI_H
#define OTHELLO_AI_H


#include <utility>
#include "GameController.h"

class AI {
public:
    AI(GameController *controller);
    std::pair<int, int> getMove();

private:
    std::pair<int, int> getBestCell();
    std::pair<int, int> getRandomCell();
    GameController *gc;
};


#endif //OTHELLO_AI_H
