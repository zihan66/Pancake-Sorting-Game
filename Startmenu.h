#include "Graph.h"
#include "Window.h"
#include "Point.h"
#include "My_button.h"
#include <iostream>
#include <fstream>
#include "HumanPlayer.h"
//#include "std_lib_facilities_5.h"
#include "AIPlayer.h"

struct Pancake_window : Graph_lib::Window
{
    Pancake_window(Player* human, Player* ai, PlayerType *winner);
    //------------------------------------------------------------------

    void update();
    void game_init();
    int difficulty;
    void nothing();
    //int ai_index;
    bool c;
    PlayerType checkGameOver();

    vector<Button *> b1;
    static void cb_instrunction(Address, Address);
    static void cb_instrunction1(Address, Address);
    //
  private:
    Button quit;
    PlayerType *winner1;
    Player* _human;
    Player* _ai;
    static void cb_quit(Address, Address);
    static void cb_button(Address, Address);
    void quit_();
    vector<My_Button *> buttons; // vector of buttons
    void handle_button(Fl_Button *button);
    void init_pancake();
    int start_position(int n);
    int find_index(int n);
    int find(Fl_Button *button);
    void update_buttons();
    //--------------------------------------------------------------------
    void update_buttons_ai();
    //PlayerType checkGameOver();
};
