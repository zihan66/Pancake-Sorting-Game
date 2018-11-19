#pragma once
#include <iostream>
#include <unistd.h>
#include "std_lib_facilities_5.h"
#include "Gui.h"
#include "Graph.h"

#include "IOManager.h"
#include "Score.h"
#include "PlayerType.h"

class GameManager
{
  private:
    int difficulty;
    int numberOfPancakes;
    string playerInitials;

    Player *leftPlayer;
    Player *rightPlayer;

    IOManager *ioManager;

  public:
    GameManager();
    ~GameManager();

    int getNumberOfPancakes();
    int getAIDifficulty(int maxDifficulty);

    int *promptForInitialStack(int size);
    int *getRandomInitialStack(int size);

    int *getInitialStack(int size);

    vector<Score> getScoresFromFile();
    string promptForInitials();
    void displayScores(string initials);
    void displaySplash();
    void displayInstructions();

    int calculateScore();

    PlayerType checkGameOver();
    string gameOver(PlayerType winner);
    void displayAndWriteFinalScore(int score, string message);
    bool promptToPlayAgain();

    void makePlayers();

    PlayerType nextTurn(PlayerType currentTurn);
    Player *getPlayer(PlayerType type);

    void initScreen();

    PlayerType gameLoop();
    void runGame();

    // test functions
    const Player *getLeftPlayer() const
    {
        return leftPlayer;
    }

    const Player *getRightPlayer() const
    {
        return rightPlayer;
    }

    void setParametersForTest(Player *left, Player *right, int n, int diff)
    {
        leftPlayer = left;
        rightPlayer = right;
        numberOfPancakes = n;
        difficulty = diff;
    }
};
