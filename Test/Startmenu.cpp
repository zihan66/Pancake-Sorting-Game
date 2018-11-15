#include "Startmenu.h"

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
    : Window{ xy, w, h, title }
    , Start(Point(315, 530), 70, 30, "Start", cb_instrunction)
	, Instrunction(Point(300, 150), "Instrunction: " )
	{
		attach(Start);
	}
	
void Lines_window::cb_instrunction(Address, Address pw)
{
	reference_to<Lines_window>(pw).start();
}

void Lines_window::start(){
	detach(Start);
	attach(Instrunction);
}
	

int main() try {
    cerr << "Program Started" << endl;
    Lines_window win{ Point{ 100, 100 }, 600, 600, "Sliding Button" };
    cerr << "Program Started" << endl;

    return gui_main();
}
catch (exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "Some exception\n";
    return 2;
}
