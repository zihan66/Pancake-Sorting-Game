#pragma once

#include <vector>

#include "Player.h"
#include "PlayerType.h"

class HumanPlayer : public Player {
private:
public:
    HumanPlayer(const vector<int>& s, PlayerType t);
    int getMove();
};
