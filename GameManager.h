#pragma once
#include <iostream>
#include <unistd.h>
#include "std_lib_facilities_5.h"
#include "GUI.h"
#include "Graph.h"
#include "Player.h"
#include "PlayerType.h"
#include "Score.h"
class GameManager
{
  private:
    int difficulty;
    int numberOfPancakes;
    string playerInitials;

    Player *leftPlayer;
    Player *rightPlayer;

  public:
    GameManager();
    ~GameManager();

    int *promptForInitialStack(int size);
    vector<int> getRandomInitialStack(int size);

    vector<Score> getScoresFromFile();
    void displayScores(string initials);

    int calculateScore();

    PlayerType checkGameOver();
    string gameOver(PlayerType winner);
    bool displayAndWriteFinalScore(int score, string message);

    void makePlayers();

    PlayerType nextTurn(PlayerType currentTurn);
    Player *getPlayer(PlayerType type);

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
