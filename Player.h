#pragma once

#include <vector>
#include "std_lib_facilities_5.h"

#include "PlayerType.h"

class Player {
protected:
    vector<int> stack;
    PlayerType type;
 public:
    Player(const vector<int>& s, PlayerType t);
    virtual ~Player();
	
	PlayerType getPlayerType() const;
    const vector<int>& getStack() const;

    void executeMove(int index);

    virtual int getMove() = 0;
};
