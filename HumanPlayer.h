#pragma once

#include "Player.h"
#include "PlayerType.h"
#include "std_lib_facilities_5.h"

class HumanPlayer : public Player {
private:
public:
    HumanPlayer(const vector<int>& s, PlayerType t);
    int getMove();
};
