#pragma once

#include <vector>

#include "AIMove.h"

class AIMoveTree {
private:
    vector<AIMoveTree*> children;
    AIMove move;
public:
    AIMoveTree(AIMove m) : move(m) { }
    ~AIMoveTree() {
        for (AIMoveTree* child : children) {
            delete child;
        }
    }

    AIMove getMove() const {
        return move;
    }

    const vector<AIMoveTree*>& getChildren() const {
        return children;
    }

    void addChild(AIMoveTree* child) {
        children.push_back(child);
    }
};
