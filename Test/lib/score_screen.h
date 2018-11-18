

#ifndef score_screen_h
#define score_screen_h

#include "std_lib_facilities_5.h"
#include "Graph.h"
#include "Window.h"
#include "Point.h"
#include "GUI.h"

#include <unistd.h>
#include <stdio.h>

using namespace Graph_lib;

struct score_screen : Graph_lib::Window {
    score_screen();
  
private:
    
    Text line0{ Point{ 60,80 }, "Thank You for playing, if" };
    Text line1{ Point{ 60,100 },"you would like to play again" };
    Text line2{ Point{ 80,140 },"-->  Please hit \"Continue\"" };
    Text line3{ Point{ 80,175},"-->  Otherwise hit \"End\"" };
    Text highScores{ Point(310, 75), "High Scores:" };
    
    Text userScore{ Point{440, 75}, "User Score:" };
    //Text user{ Point{440, 100}, "" };
    
    //Animation for game being played
  
    Button score_button1;
    Button score_button2;
    
  //
    
  
    
    static void cb_play(Address, Address);
     static void cb_quit(Address, Address);
    
    void start();
    void quit();
};



#endif

