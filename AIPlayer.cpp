#include <algorithm>
#include <limits>
#include <fstream>

#include "AIPlayer.h"

using namespace std;

AIPlayer::AIPlayer(const vector<int>& s, PlayerType t, int diff) : Player(s, t), difficulty(diff) { }

int AIPlayer::calculateSortedValue(const vector<int>& stack) {
    if (stack.size() <= 1) return 0;

    bool lt = true;
    int reversals = 0;

    for (size_t i = 0; i < stack.size() - 1; i++) {
        int elem1 = stack.at(i);
        int elem2 = stack.at(i + 1);
        if ((lt && elem1 > elem2) || (!lt && elem1 < elem2)) {
            reversals++;
            lt = !lt;
        }
    }

    return reversals;
}

AIMove AIPlayer::calculateMove(size_t flipIndex, const vector<int>& stack, vector<int>* flippedStack) {
    *flippedStack = stack;

    if (flipIndex > 0 && flipIndex < flippedStack->size()) {
        reverse(flippedStack->begin(), flippedStack->begin() + flipIndex + 1);
    }

    int sortedValue = calculateSortedValue(*flippedStack);

    return { flipIndex, sortedValue };
}

void AIPlayer::populateMoveTree(AIMoveTree* tree, const vector<int>& stack, int depth) {
    if (depth == 0) return;
    
    size_t n = stack.size();

    // start at 2nd element. flipping the first element is pointless
    for (size_t i = 1; i < n; i++) {
        vector<int> flippedStack;
        AIMove move = calculateMove(i, stack, &flippedStack);
        AIMoveTree* child = new AIMoveTree(move);

        // if the stack is completely sorted, don't keep calculating moves
        if (move.sortedValue > 0) {
            populateMoveTree(child, flippedStack, depth - 1);
        }
        
        tree->addChild(child);
    }
}

AIMoveTree* AIPlayer::getMoveTree(const vector<int>& stack, int depth) {
    int sortedValue = calculateSortedValue(stack);

    AIMoveTree* root = new AIMoveTree({ 0, sortedValue });
    populateMoveTree(root, stack, depth);

    return root;
}

pair<int, uint> AIPlayer::getMinSortedValue(const AIMoveTree* tree) {
    const vector<AIMoveTree*>& children = tree->getChildren();

    if (children.size() == 0) {
        return make_pair(tree->getMove().sortedValue, 0);
    }

    // first is sorted value, second is relative depth in tree
    pair<int, uint> min = make_pair(numeric_limits<int>::max(), numeric_limits<uint>::max());

    for (AIMoveTree* child : children) {
        pair<int, uint> minChild = getMinSortedValue(child);

        if (minChild.first < min.first) {
            min = minChild;
        }
        else if (minChild.first == min.first && minChild.second < min.second) {
            // we want to get the optimal move that is closest in the tree.
            min = minChild;
        }
    }

    return make_pair(min.first, min.second + 1);
}

size_t AIPlayer::getMinSubtree(const AIMoveTree* tree) {
    const vector<AIMoveTree*>& children = tree->getChildren();
    size_t size = children.size();
    
    // first is sorted value, second is relative depth in tree
    pair<int, uint> min = make_pair(numeric_limits<int>::max(), numeric_limits<uint>::max());
    size_t minIndex = -1;

    for (size_t i = 0; i < size; i++) {
        pair<int, uint> minChild = getMinSortedValue(children.at(i));

        if (minChild.first < min.first) {
            min = minChild;
            minIndex = i;
        }
        else if (minChild.first == min.first && minChild.second < min.second) {
            // we want to get the optimal move that is closest in the tree.
            min = minChild;
            minIndex = i;
        }
    }

    return minIndex;
}

int AIPlayer::getMove() {
    AIMoveTree* moveTree = getMoveTree(getStack(), difficulty);

    size_t bestMoveIndex = getMinSubtree(moveTree);
    
    int bestMove = moveTree->getChildren().at(bestMoveIndex)->getMove().flipAtIndex;

    delete moveTree;

    return bestMove;
}
