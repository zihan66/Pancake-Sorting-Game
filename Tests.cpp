#include <string.h>
#include <curses.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>

#include "GameManager.h"
#include "Score.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "TestPlayer.h"
#include "Test.h"

using namespace std;

// if any test name is greater than 20 characters,
// update the column width here.
#define TESTNAME_COL_WIDTH 30
#define TESTS_TABLE_WIDTH TESTNAME_COL_WIDTH + 9

#define runTest(fn) (runTestFn)(#fn, fn)

// UNIT TESTS

// example unit test format
bool sampleTest() {
    return true;
}

bool testCalculateScore() {
    vector<int> sorted = { 1, 2, 3, 4, 5 };
    vector<int> unsorted = { 4, 3, 5, 2, 1 };

    TestPlayer* left = new TestPlayer(sorted, PlayerType::LeftSide);
    TestPlayer* right = new TestPlayer(unsorted, PlayerType::RightSide);
    
    GameManager gm;
    gm.setParametersForTest(left, right, 5, 3);

    // left player sorted, right is not.
    // expected: 2 * n * (diff + 1)
    int score1 = gm.calculateScore();

    if (score1 != 40) return false;

    // both sorted
    // expected: n * (diff + 1)
    right->setStack(sorted);
    int score2 = gm.calculateScore();

    if (score2 != 20) return false;

    // right sorted, left is not
    // expected: n
    left->setStack(unsorted);
    int score3 = gm.calculateScore();

    if (score3 != 5) return false;

    return true;
}

bool testCheckGameOver() {
    vector<int> sorted = { 1, 2, 3, 4, 5 };
    vector<int> unsorted = { 4, 3, 5, 2, 1 };

    TestPlayer* left = new TestPlayer(sorted, PlayerType::LeftSide);
    TestPlayer* right = new TestPlayer(unsorted, PlayerType::RightSide);
    
    GameManager gm;
    gm.setParametersForTest(left, right, 5, 3);

    // left player wins
    PlayerType result1 = gm.checkGameOver();
    if (result1 != PlayerType::LeftSide) return false;

    // right player wins
    left->setStack(unsorted);
    right->setStack(sorted);
    PlayerType result2 = gm.checkGameOver();
    if (result2 != PlayerType::RightSide) return false;

    // no winner
    right->setStack(unsorted);
    PlayerType result3 = gm.checkGameOver();

    if (result3 != PlayerType::None) return false;

    return true;
}

bool Test::calculateSortedValue() {
    vector<int> v1 = { 1, 2, 3, 5, 4 }; // 1 reversal
    vector<int> v2 = { 1, 2, 5, 3, 4 }; // 2 reversals
    vector<int> v3 = { 1, 4, 2, 5, 3 }; // 3 reversals
    vector<int> v4 = { 5, 1, 4, 2, 3 }; // 4 reversals

    int result1 = AIPlayer::calculateSortedValue(v1);
    if (result1 != 1) return false;

    int result2 = AIPlayer::calculateSortedValue(v2);
    if (result2 != 2) return false;

    int result3 = AIPlayer::calculateSortedValue(v3);
    if (result3 != 3) return false;

    int result4 = AIPlayer::calculateSortedValue(v4);
    if (result4 != 4) return false;

    return true;
}

bool Test::calculateMove() {
    vector<int> v1 = { 1, 2, 3, 5, 4 }; // 1 reversal

    vector<int> temp;

    AIMove result1 = AIPlayer::calculateMove(0, v1, &temp);
    if (result1.sortedValue != 1) return false;

    AIMove result2 = AIPlayer::calculateMove(1, v1, &temp);
    if (result2.sortedValue != 3) return false;

    AIMove result3 = AIPlayer::calculateMove(2, v1, &temp);
    if (result3.sortedValue != 3) return false;

    AIMove result4 = AIPlayer::calculateMove(3, v1, &temp);
    if (result4.sortedValue != 2) return false;

    AIMove result5 = AIPlayer::calculateMove(4, v1, &temp);
    if (result5.sortedValue != 1) return false;

    AIMove result6 = AIPlayer::calculateMove(5, v1, &temp);
    if (result6.sortedValue != 1) return false;

    return true;
}

bool moveEquals(AIMove actual, AIMove expected) {
    return actual.flipAtIndex == expected.flipAtIndex && actual.sortedValue == expected.sortedValue;
}

bool treeEquals(AIMoveTree* actual, AIMoveTree* expected) {
    if (!moveEquals(actual->getMove(), expected->getMove())) {
        return false;
    }

    const vector<AIMoveTree*>& actualChildren = actual->getChildren();
    const vector<AIMoveTree*>& expectedChildren = expected->getChildren();

    if (actualChildren.size() != expectedChildren.size()) {
        return false;
    }

    size_t size = actualChildren.size();
    for (size_t i = 0; i < size; i++) {
        if (!treeEquals(actualChildren.at(i), expectedChildren.at(i))) {
            return false;
        }
    }

    return true;
}

AIMoveTree* getTestTree() {
    AIMoveTree* root = new AIMoveTree({ 0, 1 });
    // 3 2 1

    AIMoveTree* child1 = new AIMoveTree({ 1, 1 });
    // 2 3 1
    AIMoveTree* child11 = new AIMoveTree({ 1, 1 });
    AIMoveTree* child12 = new AIMoveTree({ 2, 1 });
    child1->addChild(child11);
    child1->addChild(child12);

    AIMoveTree* child2 = new AIMoveTree({ 2, 0 });
    // 1 2 3

    root->addChild(child1);
    root->addChild(child2);

    return root;
}

void printTree(const AIMoveTree* tree, int tab, ostream& os) {
    AIMove move = tree->getMove();
    string tabStr(tab, '\t');
    os << tabStr << '{' << move.flipAtIndex << ',' << move.sortedValue << "}:[";

    if (tree->getChildren().size() == 0) {
        os << ']' << endl;
        return;
    }

    os << endl;

    for (AIMoveTree* child : tree->getChildren()) {
        printTree(child, tab + 1, os);
    }

    os << tabStr << ']' << endl;
}

bool Test::getMoveTree() {
    vector<int> v = { 3, 2, 1 };

    AIMoveTree* actual = AIPlayer::getMoveTree(v, 2);
    AIMoveTree* expected = getTestTree();

    bool result = treeEquals(actual, expected);

    delete actual;
    delete expected;

    return result;
}

bool Test::getMinSubTree() {
    AIMoveTree* testTree = getTestTree();

    size_t result = AIPlayer::getMinSubtree(testTree);

    delete testTree;
    
    return result == 1;
}

bool Test::getMove() {
    vector<int> stack = { 3, 2, 1 };

    Player* player = new AIPlayer(stack, PlayerType::RightSide, 2);
    int move = player->getMove();

    delete player;
    
    return move == 2;
}

// END UNIT TESTS

// don't use this, call the runTest macro instead.
void runTestFn(string testName, bool (*testFn)()) {
    bool result = testFn();

    cout << left << setw(TESTNAME_COL_WIDTH) << testName << " | ";
    if (result) {
        cout << "\033[32mPASSED\033[0m" << endl;
    }
    else {
        cout << "\033[31mFAILED\033[0m" << endl;
    }
}

int main() {
    cout << left << setw(TESTNAME_COL_WIDTH) << "Test name" << " | " << "Result" << endl;
    cout << string(TESTS_TABLE_WIDTH, '=') << endl;

    // call runTest for every unit test function
    runTest(testCalculateScore);
    runTest(testCheckGameOver);
    runTest(Test::calculateSortedValue);
    runTest(Test::calculateMove);
    runTest(Test::getMoveTree);
    runTest(Test::getMinSubTree);
    runTest(Test::getMove);

    return 0;
}
