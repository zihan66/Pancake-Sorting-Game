#pragma once

#include "lib/Simple_window.h"
#include "lib/Graph.h"
#include "lib/Window.h"
#include "lib/Point.h"

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
 // 	void again(Address, Address pw);
 // 	void quit(Address, Address pw);
    EndGame(string message,// vector<Score> scores, 
    	string initials, bool* playAgain);
};