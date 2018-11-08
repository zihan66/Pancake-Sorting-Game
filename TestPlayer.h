#pragma once

#include <vector>

#include "Player.h"

class TestPlayer : public Player {
public:
    TestPlayer(const std::vector<int>& s, PlayerType t) : Player(s, t) { }

    int getMove() { return 0; }

    std::vector<int>& getStackToModify() {
        return stack;
    }

    void setStack(const std::vector<int>& s) {
        stack = s;
    }
};