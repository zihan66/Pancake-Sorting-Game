#include "lib/Simple_window.h"
#include "lib/Graph.h"
#include "lib/Window.h"
#include "lib/Point.h"
#include <iostream>
#include <fstream>

#include "AIPlayer.h"

using namespace Graph_lib; 


struct Lines_window : Graph_lib::Window {
Lines_window(Point xy, int w, int h, const string& title);

vector<int> stack;
void update();
void game_init();
int difficulty; 
void nothing();
void flip(int index);

private:
	Button next;
	AIPlayer *a;
	//Graph_lib::Text Instrunction;
	
	//vector<Rectangle*> r1;
	vector<Button*> b1;
	static void cb_instrunction(Address,Address);
	static void cb_instrunction1(Address,Address);

	int y_position(int n);

};
