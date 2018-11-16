#include "EndGame.h"

EndGame::EndGame(string message, vector<Score> scores, string initials, bool* playAgain)
    : Window(Point(100, 100), 600, 400, "Game Over"),
      _yes(Point(33, 300), 250, 80, "Yes", callbackYes),
      _no(Point(333, 300), 250, 80, "No", callbackNo),
      _playAgain(playAgain)
{
    attach(_yes);
    attach(_no);

    Fl::redraw();
    Fl::run();
}

void EndGame::callbackYes(Address, Address) {
    *(_playAgain) = true;
    hide();
}

void EndGame::callbackNo(Address, Address) {
    *(_playAgain) = false;
    hide();
}