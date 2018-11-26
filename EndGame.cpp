#include "EndGame.h"
#include "Score.h"

EndGame::EndGame(string message, vector<Score> scores, bool* playAgain)
    : Window{Point{100, 100}, 600, 400, "Game Over"},
      _yes{Point{333, 300}, 250, 20, "Replay?", [](Address, Address pw) {reference_to<EndGame>(pw).callbackYes(); }},
      _no{Point{33, 300}, 250, 20, "Quit!", [](Address, Address pw) {reference_to<EndGame>(pw).callbackNo(); }}
{
    _playAgain = playAgain;
    attach(_yes);
    attach(_no);
    vector<Text*> text;
    text.push_back(new Text(Point(200, 50), message));
    for(int i = 0; i < scores.size(); i++)
        text.push_back(new Text(Point(200, 50 + 20*(i + 1)),scores[i].getText()));
    for(auto& t: text)
        attach(*t);
    show();
    Fl::run();
}

void EndGame::callbackYes() {
    *(_playAgain) = true;
    hide();
    Fl::redraw();
}

void EndGame::callbackNo() {
    *(_playAgain) = false;
    hide();
    Fl::redraw();
}
