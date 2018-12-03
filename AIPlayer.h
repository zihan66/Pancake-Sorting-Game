#pragma once

#include <ostream>
#include <vector>

#include "Player.h"
#include "AIMoveTree.h"

using namespace std;

class AIPlayer : public Player {
private:
    int difficulty;

    // allow access for testing
    friend class Test;

    static int calculateSortedValue(const vector<int>& stack);
    static AIMove calculateMove(size_t flipIndex, const vector<int>& stack, vector<int>* flippedStack);

    static void populateMoveTree(AIMoveTree* tree, const vector<int>& stack, int depth);

    static AIMoveTree* getMoveTree(const vector<int>& stack, int depth);
    
    static pair<int, uint> getMinSortedValue(const AIMoveTree* tree);
    static size_t getMinSubtree(const AIMoveTree* tree);
public:
    AIPlayer(const vector<int>& s, PlayerType t, int diff);

    int getMove();
};
