#pragma once

#include "std_lib_facilities_5.h"
#include "Gui.h"
#include "Graph.h"

#include "Score.h"
#include "Player.h"
#include "PlayerType.h"

class IOManager {
private:
    void displayTextCentered(int y, std::string message);
    void displayEnterToContinue(int y);
	void drawPancake(long unsigned int pancakeIndex, int pancakeSize, PlayerType side, bool blink);

    WINDOW* createDialog(int height, int width);
    WINDOW* createPrompt(int height, int width, WINDOW*& inputBox);
public:
    void displayMessage(std::string message);
    std::string prompt(std::string message);
    bool promptYesNo(std::string message);
    int promptForNumber(std::string message, int min, int max);

	void showSplashScreen();
    void displayScores(const std::vector<Score>& scores);
	void displayInstructions();

    void drawAIThinking(int numberOfPancakes, int difficulty);

    void drawStacks(const Player* leftPlayer, const Player* rightPlayer);
    void blinkPancakes(long unsigned int pancakeIndex, const Player* player);
    void selectPancake(long unsigned int pancakeIndex, const Player* player);
	void deselectPancake(long unsigned int pancakeIndex, const Player* player); //will be used to stop a previously selected pancake from blinking
    int moveAndSelectPancake(const Player* player); //allows user to select their pancake in the GUI
    bool displayEndGameScreen(string message, vector<Score> scores, string initials, bool* playAgain);
};
