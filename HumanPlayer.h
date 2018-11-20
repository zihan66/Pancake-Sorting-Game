#pragma once

#include "Player.h"
#include "PlayerType.h"
#include "std_lib_facilities_5.h"

class HumanPlayer : public Player {
private:
public:
<<<<<<< HEAD
    HumanPlayer(const vector<int>& s, PlayerType t, IOManager* const ioManager);
=======
    HumanPlayer(const vector<int>& s, PlayerType t);
    int getMove();
>>>>>>> add900a81806461caf97c5553a4ce11fe45b9e4c
};
