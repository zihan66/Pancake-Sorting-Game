#include "std_lib_facilities_5.h"
#include "score_screen.h"
#include "start_screen.h"
#include "Graph.h"
#include "FL/Fl_JPEG_Image.H"
int main()
{
try {
    
    score_screen win;

 
  return Graph_lib::gui_main();
}
catch(exception& e) {
	cerr << "exception: " << e.what() << '\n';
	return 1;
}
catch (...) {
	cerr << "Some exception\n";
	return 2;
}
}
