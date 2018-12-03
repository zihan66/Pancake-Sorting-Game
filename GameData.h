#pragma once

#include <string>
#include <vector>

using namespace std;

struct GameData {
    string Initials;
    int StackHeight;
    int AIDifficulty;
    bool IsRandom;
    vector<int> Order;
};