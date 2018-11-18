

#include "start_screen.h"
#include "score_screen.h"
#include <FL/Fl_JPEG_Image.H>
#include <unistd.h>

using namespace Graph_lib;

start_screen::start_screen():Window{ Point(100,100), 600, 600, "Play again" },
// win(nullptr),
score_button1{ Point{ 480,400}, 80, 25, "Quit",cb_quit}

{
 
    
    //Aesthetics

    attach(score_button1);
    //Update the screen and wait
    Fl::redraw();
    Fl::run();
}




void start_screen::cb_quit(Address, Address pw)
{
    reference_to<start_screen>(pw).quit();
}

void start_screen::quit() {
    hide();
    score_screen win2;
}


