#include "Simple_window.h"
#include "Graph.h"
#include "Window.h"
#include "Point.h"
#include <iostream>
#include <fstream>

struct Lines_window : Graph_lib::Window {
    Lines_window(Point xy, int w, int h, const string& title);

private:
	Button Start;
	Text Instrunction;
	static void cb_instrunction(Address, Address);
	void start();
};
