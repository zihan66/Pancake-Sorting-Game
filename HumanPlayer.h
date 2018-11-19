#pragma once

#include "Player.h"
#include "IOManager.h"
#include "PlayerType.h"

class HumanPlayer : public Player {
private:
    IOManager* const ioManager;
public:
    HumanPlayer(const vector<int>& s, PlayerType t, IOManager* const ioManager);
    int getMove();
};
