#include "EndGame.h"
#include "Score.h"

EndGame::EndGame(string message, vector<Score> scores, bool* playAgain)
    : Window{Point{100, 100}, 600, 400, "Game Over"},
      _yes{Point{333, 300}, 250, 20, "Yes", [](Address, Address pw) {reference_to<EndGame>(pw).callbackYes(); }},
      _no{Point{33, 300}, 250, 20, "No", [](Address, Address pw) {reference_to<EndGame>(pw).callbackNo(); }}
{
    _playAgain = playAgain;
    attach(_yes);
    attach(_no);
    vector<In_box*> text;
    text.push_back(new In_box(Point(300, 50), 8, 10, message));
    for(int i = 0; i < scores.size(); i++)
        text.push_back(new In_box(Point(300, 50 + 20*(i + 1)), 8, 10, scores[i].getText()));
    for(auto& t: text) 
        attach(*t);
    show();
    Fl::redraw();
    Fl::run();
}

void EndGame::callbackYes() {
    *(_playAgain) = true;
    Fl::redraw();
}

void EndGame::callbackNo() {
    *(_playAgain) = false;
    Fl::redraw();
}