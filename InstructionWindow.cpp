#include "InstructionWindow.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/FL_Text_Editor.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Browser.H>

void showInstructionWindow() {

	Fl_Window *window = new Fl_Window(600, 600);
	window->set_non_modal();
	window->label("Pancake Flip!");
	Fl_Browser *editor = new Fl_Browser(0, 50, 600, 600);
	editor->load("instructions.txt");
	Fl_Text_Buffer *textbuf = new Fl_Text_Buffer();
	Fl_Box *box = new Fl_Box(0, 2, 600, 48, "Welcome to Pancake Flip!");
	box->box(FL_UP_BOX);
	box->labelfont(FL_BOLD+FL_ITALIC);
	box->labelsize(45);
	box->labeltype(FL_SHADOW_LABEL);
	Fl_Button *ok = new Fl_Button(0, 500, 600, 100, "Click to Start!");
	ok->labelsize(45);
	ok->labelcolor(fl_rgb_color(88));

	bool close = false;
	ok->callback([](Fl_Widget *w, void* c) {
		Fl_Widget *p = w->parent();
		*((bool*)c) = true;
		((Fl_Window*)p)->iconize();
	}, &close);
	window->end();
	window->position((Fl::w() - window->w())/2, (Fl::h() - window->h())/2);  
	window->show(0, nullptr);
	while (window->shown())  {
		if (!close) {
				Fl::wait();
		} else break;
	}
  	Fl::modal();
 }