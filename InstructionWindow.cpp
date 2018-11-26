#include "InstructionWindow.h"
InstructionWindow::InstructionWindow(Point xy, int w, int h, const string& title)
	:Window{ xy, w, h, title }
	,start_(Point{ 100, 500 }, 400, 100, "Start", cb_start)
	,c(Point{0, 0},"pic.jpg")
	{
		attach(start_);
		attach(c);
		Fl::run();
	}

void InstructionWindow::cb_start(Address, Address pw)
{
    reference_to<InstructionWindow>(pw).start();
}

void InstructionWindow::start(){
		hide();
}
