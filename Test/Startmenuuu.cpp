#include "Startmenu.h"
using namespace std;

#include <vector>




Lines_window::Lines_window(Point xy, int w, int h, const string& title)
    : Window{ xy, w, h, title }
    ,next(Point(315, 530), 70, 30, "next", cb_instrunction)
	{

    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

	int d = 3;
    	a = new AIPlayer(v, PlayerType::RIGHTSIDE, d);
        attach(next);

	}


void Lines_window::cb_instrunction(Address, Address pw)
{

    reference_to<Lines_window>(pw).update();
    
    int index = a->getMove();

    flip(index);


}


void Lines_window::update()
{



    for(int i=0;i<b1.size();i++)
      {  
        detach(*(b1.at(i)));
      }

    cerr << "update pancake" << endl;

    b1.clear();

    int index = a->getMove();

    flip(index);


    //game_init();


}

void Lines_window::flip(int index)
{

 if (index > 0 && index < (int)stack.size()) {
        reverse(stack.begin(), stack.begin() + index + 1);
        reverse(b1.begin(),b1.begin()+index+1);
    }

}

void Lines_window::game_init()
{

    int start_y = y_position(stack.size());
    int width = 40;
    int center =380;
    int x=5;
    string label;

for(int i=0;i<stack.size();i++)
{
    label = to_string(stack[i]); 

    b1.push_back(new Button(Point(center-x,start_y),width,40,label,cb_instrunction1));

    attach(*(b1.at(i)));

    width += 10;
    start_y += 50;
    x +=5;

}


}
void Lines_window::cb_instrunction1(Address, Address pw)
{

    reference_to<Lines_window>(pw).nothing();

}

void Lines_window::nothing()
{
}

int Lines_window::y_position(int n)
{
int y = 320-40*n;
return y;
}

	
int main() try {
    cerr << "Program Started" << endl;
    Lines_window win{ Point{ 100, 100 }, 600, 600, "Sliding Button" };
    cerr << "Program Started" << endl;

    vector<int> test;
    test.push_back(3);
    test.push_back(1);
    test.push_back(2);
    test.push_back(4);
    win.stack=test;

    win.game_init();


   



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
