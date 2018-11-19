#include <algorithm>

#include "Player.h"

using namespace std;

// vector constructor deep copies
Player::Player(const vector<int>& s, PlayerType t) : stack(s) {
	type = t;
}

Player::~Player() { }

const vector<int>& Player::getStack() const {
    return stack;
}

PlayerType Player::getPlayerType() const {
	return type;
}

void Player::executeMove(int index) {
    if (index > 0 && index < (int)stack.size()) {
        reverse(stack.begin(), stack.begin() + index + 1);
    }
}