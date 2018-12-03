#include <fstream>

#include "HumanPlayer.h"

#define MOVE "click.txt"

using namespace std;

HumanPlayer::HumanPlayer(const vector<int> &s, PlayerType t) : Player(s, t) {}
int HumanPlayer::getMove()
{
    int ret = -1;
    while(ret < 0) {
        ifstream moveFile(MOVE);
        if(moveFile.peek() != ifstream::traits_type::eof())
            moveFile >> ret;
        
        moveFile.close();
    }

    ofstream moveFile;
    moveFile.open(MOVE, ofstream::out | ofstream::trunc);

    return ret;
};
