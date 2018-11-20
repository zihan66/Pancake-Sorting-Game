#pragma once

#include "Window.h"
#include "Point.h"

using namespace Graph_lib;

class SetupScreen : Graph_lib::Window
{
	private:
		In_box inits;
		Text scores;
		Fl_Hor_Nice_Slider numPans;
		Fl_Hor_Nice_Slider diff;
		Fl_Round_Button randY;
		Fl_Round_Button randN;
		
		bool InputPans;
		int numP;
		int diff;
		string initials;
		
		static void callbackRandY(Fl_Widget *butt, void *d);

	public:
		SetupGame();
<<<<<<< HEAD
}
=======
}
>>>>>>> add900a81806461caf97c5553a4ce11fe45b9e4c
