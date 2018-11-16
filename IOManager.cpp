#include <algorithm>
#include <sstream>
#include <string>
#include <stdexcept>
#include <unistd.h>
#include <cmath>

#include <curses.h>

#include "Window.h"
#include "Point.h"

#include "IOManager.h"

using namespace std;

void IOManager::displayTextCentered(int y, string message) {
    int maxX = getmaxx(stdscr);
    mvaddstr(y, (maxX - message.length())/2, message.c_str());
}

void IOManager::displayEnterToContinue(int y) {
    int maxX = getmaxx(stdscr);
    
    // 24 = length of "Press ENTER to continue."
    mvaddstr(y, (maxX - 24) / 2, "Press ");
    attron(A_BLINK);
    addstr("ENTER");
    attroff(A_BLINK);
    addstr(" to continue.");
}

WINDOW* IOManager::createDialog(int height, int width) {
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    WINDOW* win = newwin(height, width, (maxY - height) / 2, (maxX - width) / 2);
    wbkgd(win, COLOR_PAIR(1));
    wrefresh(win);

    return win;
}

WINDOW* IOManager::createPrompt(int height, int width, WINDOW*& inputBox) {
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    WINDOW* win = newwin(height, width, (maxY - height) / 2, (maxX - width) / 2);
    wbkgd(win, COLOR_PAIR(1));

    inputBox = derwin(win, 1, width - 2, height - 2, 1);
    wbkgd(inputBox, COLOR_PAIR(2));

    touchwin(win);
    wrefresh(win);

    return win;
}

size_t getWidthAndSplit(string message, vector<string>& v) {
    istringstream ss(message);

    size_t width = 0;

    string line;
    while (getline(ss, line)) {
        v.push_back(line);
        if (line.length() > width) {
            width = line.length();
        }
    }

    return width;
}

void moveAddMultilineString(WINDOW* win, int y, int x, const vector<string>& v) {
    for (size_t i = 0; i < v.size(); i++) {
        mvwaddstr(win, y + i, x, v.at(i).c_str());
    }
}

void IOManager::displayMessage(string message) {
    clear();
    refresh();

    vector<string> messageV;
    int height = 3 + count(message.begin(), message.end(), '\n');
    int width = getWidthAndSplit(message, messageV) + 2;
    WINDOW* diag = createDialog(height, width);

    moveAddMultilineString(diag, 1, 1, messageV);
    wrefresh(diag);

    noecho();
    curs_set(0);
    wgetch(diag);

    delwin(diag);
    clear();
    refresh();
}

string IOManager::prompt(string message) {
    clear();
    refresh();

    vector<string> messageV;
    getWidthAndSplit(message, messageV);
    int height = 5 + count(message.begin(), message.end(), '\n');
    WINDOW* inputWin;
    WINDOW* prompt = createPrompt(height, 60, inputWin);

    moveAddMultilineString(prompt, 1, 1, messageV);
    wrefresh(prompt);

    echo();
    curs_set(1);
    char input[128];
    wgetnstr(inputWin, input, 128);
    noecho();
    curs_set(0);

    delwin(inputWin);
    delwin(prompt);
    clear();
    refresh();

    return string(input);
}

bool IOManager::promptYesNo(string message) {
    while (true) {
        string input = prompt(message);

        if (tolower(input.front()) == 'y') {
            return true;
        }
        else if (tolower(input.front() == 'n')) {
            return false;
        }
        else {
            beep();
        }
    }
}

int IOManager::promptForNumber(string message, int min, int max) {
    int number;

    while (true) {
        string input = prompt(message);

        try {
            number = stoi(input);
        }
        catch (invalid_argument& e) {
            beep();
            continue;
        }

        if (number < min || number > max) {
            beep();
            continue;
        }

        // if we've reached this point, the entered number is valid.
        break;
    }
    
    return number;
}
	
void IOManager::showSplashScreen() {
	clear();
	
    int startY = (getmaxy(stdscr) - 11) / 2;

    displayTextCentered(startY, "Welcome to Pancake Flip!");
    displayTextCentered(startY + 2, "We are Team 21 - \"Blackjack and ... other things\"");
    displayTextCentered(startY + 4, "TEAM MEMBERS:");
    displayTextCentered(startY + 5, "Garrett Oelze");
    displayTextCentered(startY + 6, "Joey Whitmore");
    displayTextCentered(startY + 7, "Branden Klar");
    displayTextCentered(startY + 8, "Zachary Stachowiak");
    
    displayEnterToContinue(startY + 10);
	
	nocbreak(); // only enter character are valid input now
	getch(); // will wait for enter
	cbreak(); // return to normal
}

void IOManager::displayInstructions() {
	clear();

    int startY = (getmaxy(stdscr) - 14) / 2;

    displayTextCentered(startY, "HOW TO PLAY:");
	displayTextCentered(startY + 2, "You will start with an out-of-order stack of pancakes of different sizes");
    displayTextCentered(startY + 3, "The objective is to order the stack from smallest to largest at the bottom");
    displayTextCentered(startY + 4, "To play you will select a pancake, and it will flip each pancake above it");

    displayTextCentered(startY + 6, "Use the arrow keys to select a pancake, then 'Enter' to flip at that point.");
    displayTextCentered(startY + 7, "Press 'h' for a hint.");

    displayTextCentered(startY + 9, "You will be playing against an AI and your goal is to beat it.");
    displayTextCentered(startY + 10, "Your score will increase with harder AI and more pancakes.");
    displayTextCentered(startY + 11, "Good luck and have fun!");
	
	displayEnterToContinue(startY + 13);
	
	nocbreak(); // only enter character are valid input now
	getch(); // will wait for enter
	cbreak(); // return to normal
}

void IOManager::displayScores(const vector<Score>& scores) {
    clear();
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    int y = (maxY - scores.size() - 2) / 2;
    int x = (maxX - 11) / 2;

    mvprintw(y, x, "HIGH SCORES");

    y += 2;

    for (const Score& score : scores) {
        mvprintw(y++, x, "%3s %7d", score.initials.c_str(), score.score);
    }

    refresh();

    displayEnterToContinue(y + 1);
    nocbreak(); // only enter character are valid input now
	getch(); // will wait for enter
	cbreak(); // return to normal
}

void IOManager::drawAIThinking(int numberOfPancakes, int difficulty) {
    unsigned long nodeCount = pow((double)(numberOfPancakes - 1), (double)(difficulty + 1)) - 1;

    displayTextCentered(27, "The AI is thinking...");
    displayTextCentered(28, "Searching an estimated " + to_string(nodeCount) + " nodes.");
    refresh();
}

void IOManager::drawStacks(const Player* leftPlayer, const Player* rightPlayer) {
    clear();
	mvaddstr(0, 17, "Human");
	mvaddstr(0, 59, "AI");
	const vector<int>& lstack = leftPlayer->getStack();
	const vector<int>& rstack = rightPlayer->getStack();
	for (unsigned long int i = 0; i < lstack.size(); i++) { //lstack size should == rstack size, otherwise something else broke
		drawPancake(i, lstack.at(i), leftPlayer->getPlayerType(), false);
		drawPancake(i, rstack.at(i), rightPlayer->getPlayerType(), false);
	}

    int movesLeft = leftPlayer->getSolution().size();

    displayTextCentered(36, "Minimum number of moves left: " + to_string(movesLeft));
    displayTextCentered(38, "Press 'h' for hint.");

    refresh();
}

void IOManager::blinkPancakes(long unsigned int pancakeIndex, const Player* player) {
    const vector<int>& stack = player->getStack();
	if(stack.size() < pancakeIndex)
		pancakeIndex = stack.size() - 1; //make sure pancakeIndex is valid
	for(long unsigned int i = 0; i <= pancakeIndex; i++)
		drawPancake(i, stack.at(i), player->getPlayerType(), true);
    refresh();
	sleep(3);
	for(long unsigned int i = 0; i <= pancakeIndex; i++)
		drawPancake(i, stack.at(i), player->getPlayerType(), false);
    refresh();
}

void IOManager::selectPancake(long unsigned int pancakeIndex, const Player* player) {
    const vector<int>& stack = player->getStack();
	if(stack.size() < pancakeIndex)
		pancakeIndex = stack.size() - 1; //make sure pancakeIndex is valid
	drawPancake(pancakeIndex, stack.at(pancakeIndex), player->getPlayerType(), true);
    refresh();
}

void IOManager::deselectPancake(long unsigned int pancakeIndex, const Player* player) {
    const vector<int>& stack = player->getStack();
	if(stack.size() < pancakeIndex)
		pancakeIndex = stack.size() - 1; //make sure pancakeIndex is valid
	drawPancake(pancakeIndex, stack.at(pancakeIndex), player->getPlayerType(), false);
    refresh();
}

int mod(int a, int b) {
    return (a % b + b) % b;
}

int IOManager::moveAndSelectPancake(const Player* player) {
    int pancakeIndex = 0;
    selectPancake(pancakeIndex, player);
    int choice = 0;
    int size = player->getStack().size();
    while (true) {
        choice = getch();

        if (choice == 10) {
            return pancakeIndex;
        }

        deselectPancake(pancakeIndex, player);

        if (choice == KEY_UP) {
            pancakeIndex = mod(pancakeIndex - 1, size);
        }
        else if (choice == KEY_DOWN) {
            pancakeIndex = mod(pancakeIndex + 1, size);
        }
        else if (tolower(choice) == 'h') {
            pancakeIndex = player->getSolution().front();
        }

        selectPancake(pancakeIndex, player);

        refresh();
    }
    return 0;
}

void IOManager::drawPancake(long unsigned int pancakeIndex, int pancakeSize, PlayerType side, bool blink) {
    int yStart = pancakeIndex * 3 + 1;
    int xStart = 20 - (pancakeSize + 1); // assume left side
    if (side == PlayerType::RightSide)
        xStart = 60 - (pancakeSize + 1);
    string topBot = "+";
    string middle = "|";
    for (int i = 0; i < 2 * pancakeSize - 1; i++) {
        topBot += '-';
        if (i == pancakeSize - 1)
            middle = middle + to_string(pancakeSize);
        else
            middle += ' ';
    }
    topBot += '+';
    middle += '|';
    if (blink) {
        attron(A_BLINK);
    }
    mvaddstr(yStart, xStart, topBot.c_str());
    mvaddstr(yStart + 1, xStart, middle.c_str());
    mvaddstr(yStart + 2, xStart, topBot.c_str());
    if (blink) {
        attroff(A_BLINK);
    }
}

bool displayEndGameScreen(string message, vector<Score> scores, string initials, bool* playAgain) {
    Graph_lib::EndGame endGame(message, scores, initials, playAgain);
}