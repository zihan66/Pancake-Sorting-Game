

#ifndef start_screen_h
#define start_screen_h

#include "std_lib_facilities_5.h"
#include "Graph.h"
#include "Window.h"
#include "Point.h"
#include "GUI.h"
#include "score_screen.h"
#include <unistd.h>
#include <stdio.h>

using namespace Graph_lib;

struct start_screen : Graph_lib::Window {
    start_screen();
    
private:
    
     Button score_button1;
    
    
    score_screen* win1;
    //Animation for game being played
  
    
  //
    
    void start();
    void quit();
    
   
     static void cb_quit(Address, Address);
};



#endif

