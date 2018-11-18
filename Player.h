#pragma once

#include <vector>

#include "PlayerType.h"

class Player {
protected:
    std::vector<int> stack;
    PlayerType type;
 public:
    Player(const std::vector<int>& s, PlayerType t);
    virtual ~Player();
	
	PlayerType getPlayerType() const;
    const std::vector<int>& getStack() const;

    std::vector<int> getSolution() const;
    void executeMove(int index);

    virtual int getMove() = 0;
};
