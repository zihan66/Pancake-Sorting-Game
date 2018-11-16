#pragma once

#include "Window.h"
#include "Point.h"

using namespace Graph_lib;

class EndGame : Graph_lib::Window
{
  private:
    bool* _playAgain;
    Button _yes;
    Button _no;

    static void callbackYes(Address, Address);
    static void callbackNo(Address, Address);
  public:
    EndGame(string message, vector<Score> scores, string initials, bool* playAgain);
};