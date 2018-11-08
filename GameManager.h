#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

#include "IOManager.h"
#include "Score.h"
#include "PlayerType.h"

class GameManager {
private:
    int difficulty;
    int numberOfPancakes;
    std::string playerInitials;

    Player* leftPlayer;
    Player* rightPlayer;

    IOManager* ioManager;
public:
    GameManager();
    ~GameManager();

    int getNumberOfPancakes();
    int getAIDifficulty(int maxDifficulty);

    int* promptForInitialStack(int size);
    int* getRandomInitialStack(int size);

    int* getInitialStack(int size);
	
    std::vector<Score> getScoresFromFile();
    std::string promptForInitials();
    void displayScores(std::string initials);
	void displaySplash();
	void displayInstructions();

    int calculateScore();

    PlayerType checkGameOver();
    void displayGameOver(PlayerType winner);
    void displayAndWriteFinalScore(int score);
    bool promptToPlayAgain();

    void makePlayers();

    PlayerType nextTurn(PlayerType currentTurn);
    Player* getPlayer(PlayerType type);

    void initScreen();

    PlayerType gameLoop();
    void runGame();

    // test functions
    const Player* getLeftPlayer() const {
        return leftPlayer;
    }

    const Player* getRightPlayer() const {
        return rightPlayer;
    }

    void setParametersForTest(Player* left, Player* right, int n, int diff) {
        leftPlayer = left;
        rightPlayer = right;
        numberOfPancakes = n;
        difficulty = diff;
    }
};
