

#include "score_screen.h"
#include "start_screen.h"
#include <FL/Fl_JPEG_Image.H>
#include <unistd.h>

using namespace Graph_lib;

score_screen::score_screen():Window{ Point(100,100), 600, 600, "High Scores" },
score_button1{ Point{ 480,400}, 80, 25, "Play Again",cb_play },
score_button2{ Point{ 480,510 }, 80, 25, "Quit",cb_quit }
{
  
    
    //Aesthetics
   
    line0.set_font_size(18);
    line1.set_font_size(18);
    line2.set_font_size(18);
    line3.set_font_size(18);
    
    line0.set_color(Color::black);
    line1.set_color(Color::black);
    line2.set_color(Color::black);
    line3.set_color(Color::black);
 
    attach(score_button1);
     attach(score_button2);
    
    

    
    //Update the screen and wait
    Fl::redraw();
    Fl::run();
}


void score_screen::cb_play(Address, Address pw)
{
    reference_to<score_screen>(pw).start();
}

void score_screen::cb_quit(Address, Address pw)
{
    reference_to<score_screen>(pw).quit();
}

void score_screen::quit() {
    hide();
  
}


void score_screen::start() {
    hide();
   start_screen win2;
}
