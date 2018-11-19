#include "HumanPlayer.h"

using namespace std;

HumanPlayer::HumanPlayer(const vector<int>& s, PlayerType t, IOManager* const ioManager) : Player(s, t), ioManager(ioManager)  { }

int HumanPlayer::getMove() {
    return ioManager->moveAndSelectPancake(this);
}
