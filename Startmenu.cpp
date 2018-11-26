#include "Startmenu.h"
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <unistd.h>

Pancake_window::Pancake_window(Player *human, Player *ai, PlayerType *winner)
    : Window{Point{100, 100}, 600, 600, "Pancake Game"}, quit(Point(430, 530), 70, 30, "Quit", cb_quit), c(false)
{
    _human = human;
    _ai = ai;
    winner1 = winner;

    init_pancake();
    attach(quit);

    game_init();
    Fl::run();
}

int Pancake_window::find_index(int n)
{
    for (int i = 0; i < _human->getStack().size(); i++)
    {
        if (n == _human->getStack().at(i))
        {
            return i;
        }
    }
}

void Pancake_window::init_pancake()
{
    int start_y = start_position(_human->getStack().size()); // get y position of the smallest button
    int width = 40;
    int center = 115;
    int x = 5;
    string label;
    for (int i = 0; i < _human->getStack().size(); i++)
    {
        label = std::to_string(_human->getStack().at(i));
        width = 30 + _human->getStack().at(i) * 10;
        buttons.push_back(new My_Button(Point{center - width / 2, start_y}, width, 40, label, cb_button));

        attach(*buttons[i]);
        start_y += 50;
    }
    Text *Human = new Text(Point(86, 35), "Human Player: ");
    attach(*Human);
}

void Pancake_window::update_buttons()
{
    int start_y = start_position(_human->getStack().size()); // get y position of the smallest button
    int width;
    int center = 115;
    string label;

    for (int i = 0; i < _human->getStack().size(); i++)
    {
        detach(*buttons[i]);
    }
    buttons.clear();
    for (int i = 0; i < _human->getStack().size(); i++)
    {
        label = std::to_string(_human->getStack().at(i));
        width = 30 + _human->getStack().at(i) * 10;
        buttons.push_back(new My_Button(Point{center - width / 2, start_y}, width, 40, label, cb_button));
        attach(*buttons[i]);
        start_y += 50;
    }
    redraw();
}

int Pancake_window::start_position(int n)
{
    int y = 320 - 40 * n;
    return y;
}

void Pancake_window::cb_quit(Address, Address pw)
{
    reference_to<Pancake_window>(pw).quit_();
}

void Pancake_window::quit_()
{
    hide();
}
void Pancake_window::cb_button(Address ab, Address pw)
{
    Pancake_window *pancake_window = (Pancake_window *)pw;
    Fl_Button *button = (Fl_Button *)ab;
    pancake_window->handle_button(button);
}

void Pancake_window::handle_button(Fl_Button *button)
{

    PlayerType final_winner = PlayerType::Neither;

    int n = find(button);
    int index = find_index(n);
    usleep(200000);
    _human->executeMove(index);

    if (index > 0 && index < buttons.size())
    {
        std::reverse(buttons.begin(), buttons.begin() + index + 1);
    }
    update_buttons();

    int ai_index = _ai->getMove();

    _ai->executeMove(ai_index);

    if (ai_index > 0 && ai_index < b1.size())
        std::reverse(b1.begin(), b1.begin() + ai_index + 1);

    update_buttons_ai();

    final_winner = checkGameOver();

    if (final_winner != PlayerType::Neither)
    {
        *winner1 = final_winner;
        hide();
    }
}

int Pancake_window::find(Fl_Button *button)
{
    for (int i = 0; i < buttons.size(); i++)
    {
        if ((My_Button *)buttons[i]->is(button))
            return std::stoi(buttons[i]->label);
    }
}

//-----------------------------------------------------------------------

void Pancake_window::update_buttons_ai()
{

    int start_y = start_position(_ai->getStack().size()); // get y position of the smallest button
    int width;
    int center = 380;
    string label;

    for (int i = 0; i < _ai->getStack().size(); i++)
    {
        detach(*b1[i]);
    }
    b1.clear();

    for (int i = 0; i < _ai->getStack().size(); i++)
    {
        label = std::to_string(_ai->getStack().at(i));
        width = 30 + _ai->getStack().at(i) * 10;
        b1.push_back(new Button(Point(center - width / 2, start_y), width, 40, label, cb_instrunction1));
        attach(*b1[i]);
        start_y += 50;
    }
    redraw();
}

PlayerType Pancake_window::checkGameOver()
{
    const vector<int> &leftStack = _human->getStack();
    const vector<int> &rightStack = _ai->getStack();
    bool leftSorted = is_sorted(leftStack.begin(), leftStack.end());
    bool rightSorted = is_sorted(rightStack.begin(), rightStack.end());

    if (leftSorted && rightSorted)
        return PlayerType::Both;
    if (leftSorted || rightSorted)
        return (leftSorted) ? PlayerType::LeftSide : PlayerType::RightSide;
    return PlayerType::Neither;
}

void Pancake_window::game_init()
{
    int start_y = start_position(_ai->getStack().size());
    int width = 40;
    int center = 380;
    int x = 5;
    string label;

    for (int i = 0; i < _ai->getStack().size(); i++)
    {
        label = to_string(_ai->getStack()[i]);

        width = 30 + _ai->getStack().at(i) * 10;

        b1.push_back(new Button(Point(center - width / 2, start_y), width, 40, label, cb_instrunction1));

        attach(*(b1.at(i)));

        start_y += 50;
        x += 5;
    }

    Text *aiHeader = new Text(Point(350, 35), "AI Player: ");
    attach(*aiHeader);
}

void Pancake_window::cb_instrunction1(Address, Address pw)
{
    reference_to<Pancake_window>(pw).nothing();
}

void Pancake_window::nothing()
{
}
