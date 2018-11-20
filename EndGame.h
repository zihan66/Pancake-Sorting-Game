#pragma once

#include "std_lib_facilities_5.h"

#include "Score.h"

#include "GUI.h"

#include "Window.h"
#include "Point.h"

using namespace Graph_lib;

class EndGame : Graph_lib::Window
{
  private:
    bool* _playAgain;
    Button _yes;
    Button _no;

  public:
    EndGame(string message, vector<Score> scores,  bool* playAgain);
    void callbackYes();
    void callbackNo();
    void wait() {
        Fl::wait();
    }
};