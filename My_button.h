#include "Simple_window.h"
#include "Graph.h"
#include "Window.h"
#include "Point.h"

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
struct My_Button :Graph_lib::Button{
  My_Button(Point xy, int w, int h, const string& label, Callback cb)
		: Button(xy, w, h, label, cb)
    {}
    bool is(Fl_Button* fl) { return fl == pw; }
    void set_colors(Fl_Color back, Fl_Color font) {
		pw->Fl_Widget::color(back, Color::black);
		pw->Fl_Widget::labelcolor(font);
	}
};
