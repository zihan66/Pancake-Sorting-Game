#include <algorithm>

#include "Player.h"
#include "find_solution.h"

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

vector<int> Player::getSolution() const {
    vector<int>* foundSolution = find_solution(getStack());

    vector<int> solution;

    for (int& step : *foundSolution) {
        solution.push_back(step - 1);
    }

    delete foundSolution;

    return solution;
}
