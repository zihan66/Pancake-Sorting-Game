<<<<<<< HEAD
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
=======
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
>>>>>>> add900a81806461caf97c5553a4ce11fe45b9e4c
