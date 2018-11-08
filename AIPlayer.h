#pragma once

#include <vector>
#include <ostream>

#include "Player.h"
#include "AIMoveTree.h"
#include "Test.h"

class AIPlayer : public Player {
private:
    int difficulty;

    // allow access for testing
    friend class Test;

    static int calculateSortedValue(const std::vector<int>& stack);
    static AIMove calculateMove(size_t flipIndex, const std::vector<int>& stack, std::vector<int>* flippedStack);

    static void populateMoveTree(AIMoveTree* tree, const std::vector<int>& stack, int depth);

    static AIMoveTree* getMoveTree(const std::vector<int>& stack, int depth);
    
    static std::pair<int, uint> getMinSortedValue(const AIMoveTree* tree);
    static size_t getMinSubtree(const AIMoveTree* tree);
public:
    AIPlayer(const std::vector<int>& s, PlayerType t, int diff);

    int getMove();
};
