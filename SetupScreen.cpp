#include "SetupScreen.h"

SetupScreen::SetupScreen()
	 : Window(Point(100,100), 600, 400, "Setup"),
	numPans(400, 200, 500, 50, "Number of Pancakes".c_str()),
	diff(400, 275, 500, 50, "Difficulty".c_str()),
	randY(300, 350, 40, 40, "Random Order"),
	randN(500, 350, 40, 40, "Select Order")
	{
		randY.callback(callbackRand, (void*)1)
		randX.callback(callbackRand, (void*)0)
		attach() // everything
	}
	
void callbackRand(Fl_Widget *butt, void *d)
{
	
}