#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

#include "GameData.h"
#include "Player.h"
#include "PlayerType.h"
#include "Score.h"

using namespace std;

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

    vector<int> getRandomInitialStack(int size);

    vector<Score> getScoresFromFile();

    int calculateScore();

    GameData getGameData(string filename);

    PlayerType checkGameOver();
    string gameOver(PlayerType winner);
    void writeFinalScore(int score);
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
