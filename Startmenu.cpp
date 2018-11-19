#include "Startmenu.h"
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <unistd.h>

Pancake_window::Pancake_window(Point xy, int w, int h, const string& title)
    : Window{ xy, w, h, title }
    , quit(Point(515, 530), 70, 30, "Quit", cb_quit)
    , next(Point(315, 530), 70, 30, "next", cb_instrunction)
	  {
		 v.push_back(2);
		 v.push_back(6);
		 v.push_back(4);
         v.push_back(7);
		 v.push_back(1);
		 v.push_back(5);

    human = new HumanPlayer(v, PlayerType::LEFTSIDE);
    humanstack = human->getStack();

		init_pancake();
		attach(quit);
        AIstack = v;        
        game_init();

    a = new AIPlayer(v, PlayerType::RIGHTSIDE, 5);
     ai_index = a->getMove();

        attach(next);
	}

int Pancake_window::find_index(int n){
  for(int i = 0; i < humanstack.size() ; i++){
    if(n == humanstack.at(i)){
      return i;
    }
  }
}

void Pancake_window::init_pancake(){
	int start_y = start_position(humanstack.size()); // get y position of the smallest button
	int width = 40;
	int center = 115;
	int x = 5;
	string label;
  for(int i = 0; i < humanstack.size() ; i++){
    label = std::to_string(humanstack.at(i));
    width = 30 + humanstack.at(i)*10;
		buttons.push_back(new My_Button(Point{center-width/2, start_y}, width, 40, label , cb_button));
    //buttons[i]->set_colors(fl_rgb_color(20,58,19),fl_rgb_color(20,58,19));
		attach(*buttons[i]);
		start_y+=50;
	}
}

void Pancake_window::update_buttons(){
  int start_y = start_position(humanstack.size()); // get y position of the smallest button
	int width;
	int center = 115;
  string label;

  humanstack = human->getStack();

  for(int i = 0; i < humanstack.size(); i++){
    detach(*buttons[i]);
  }
  buttons.clear();
	for(int i = 0; i < humanstack.size(); i++){
    label = std::to_string(humanstack.at(i));
    width = 30 + humanstack.at(i) * 10;
		buttons.push_back(new My_Button(Point{center-width/2, start_y}, width, 40, label, cb_button));
    //buttons[i]->set_colors(fl_rgb_color(20,58,19),fl_rgb_color(20,58,19));
		attach(*buttons[i]);
		start_y+=50;
	}
  redraw();
}

int Pancake_window::start_position(int n){
	int y = 320 - 40*n;
	return y;
}

void Pancake_window::cb_quit(Address, Address pw)
{
	reference_to<Pancake_window>(pw).quit_();
}

void Pancake_window::quit_(){
	hide();
}
void Pancake_window::cb_button(Address ab, Address pw){
  Pancake_window* pancake_window = (Pancake_window*) pw;
  Fl_Button* button = (Fl_Button*)ab;
  pancake_window->handle_button(button);

}
void Pancake_window::handle_button(Fl_Button* button){
  int n = find(button);
  int index = find_index(n);
  for(int i=0;i<3;i++){
    detach(*buttons[index]);
    redraw();
    usleep(200000);
    attach(*buttons[index]);
    redraw();
  }
  human->executeMove(index);
  //cerr<<humanstack[0];

  if(index > 0 && index < buttons.size()) {
        std::reverse(buttons.begin(),buttons.begin()+index+1);
  }
	update_buttons();


}

int Pancake_window::find(Fl_Button* button){
  for(int i=0;i<buttons.size();i++){
    if((My_Button*)buttons[i]->is(button))
      return std::stoi(buttons[i]->label);

  }
}

//-----------------------------------------------------------------------

void Pancake_window::cb_instrunction(Address, Address pw)
{

    reference_to<Pancake_window>(pw).update();

    
   // int index = a->getMove();

  //  flip(index); 
}


void Pancake_window::update()
{



    for(int i=0;i<b1.size();i++)
      {  
        detach(*(b1.at(i)));
      }

    cerr << "update pancake" << endl;

    b1.clear();

   // int index = a->getMove();

    if(ai_index > 0 && ai_index < b1.size()) {
        std::reverse(b1.begin(),b1.begin()+ai_index+1);
        std::reverse(AIstack.begin(),AIstack.begin()+ai_index+1);
  }

    game_init();

}

void Pancake_window::game_init()
{

    int start_y = start_position(AIstack.size());
    int width = 40;
    int center =380;
    int x=5;
    string label;

for(int i=0;i<AIstack.size();i++)
{
    label = to_string(AIstack[i]); 

    width = 30 + AIstack.at(i)*10;

    b1.push_back(new Button(Point(center-width/2,start_y),width,40,label,cb_instrunction1));

    attach(*(b1.at(i)));

  //  width += 10;
   
    start_y += 50;
    x +=5;


}

}
void Pancake_window::cb_instrunction1(Address, Address pw)
{

    reference_to<Pancake_window>(pw).nothing();

}

void Pancake_window::nothing()
{
}


int main() try {
    cerr << "Program Started" << endl;
    Pancake_window win{ Point{ 100, 100 }, 600, 600, "Sliding Button" };
    cerr << "Program Started" << endl;

   // win.init_pancake();

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
