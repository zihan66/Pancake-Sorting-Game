#include "Simple_window.h"
#include "Graph.h"
#include "Window.h"
#include "Point.h"
#include "My_button.h"
#include <iostream>
#include <fstream>
#include "HumanPlayer.h"
#include "std_lib_facilities_5.h"
#include "AIPlayer.h"
#include "lib/Simple_window.h"
#include "lib/Graph.h"
#include "lib/Window.h"
#include "lib/Point.h"
struct Pancake_window : Graph_lib::Window {
    Pancake_window(Point xy, int w, int h, const string& title);
//------------------------------------------------------------------

 vector<int> AIstack;
void update();
void game_init();
int difficulty; 
void nothing();
//void flip(int index);
int ai_index;


	vector<Button*> b1;
	static void cb_instrunction(Address,Address);
	static void cb_instrunction1(Address,Address);
//
private:
	Button quit;
	Button next;
AIPlayer* a;
	static void cb_quit(Address,Address);
  static void cb_button(Address,Address);
	void quit_();
  vector<My_Button*> buttons; // vector of buttons
  HumanPlayer* human;
	void handle_button(Fl_Button* button);
	void init_pancake();
	int start_position(int n);
  int find_index(int n);
  int find(Fl_Button* button);
  void update_buttons();
  vector<int> humanstack;
  vector<int> v;
//--------------------------------------------------------------------
 

 //	
	
 


};
