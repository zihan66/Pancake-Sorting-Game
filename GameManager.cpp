#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>

#include "EndGame.h"

#include "GameManager.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"

#define FILENAME "scores"

using namespace std;

GameManager::GameManager() : leftPlayer(0), rightPlayer(0) {}

GameManager::~GameManager()
{
    if (leftPlayer != 0)
        delete leftPlayer;
    if (rightPlayer != 0)
        delete rightPlayer;
}

int *GameManager::getRandomInitialStack(int size)
{
    int *stack = new int[size];
    for (int i = 0; i < size; i++)
    {
        stack[i] = i + 1;
    }

    bool sorted = true;
    while (sorted)
    {
        // get a random seed and use it in shuffle to randomize the array.
        int seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(&stack[0], &stack[size], default_random_engine(seed));

        sorted = is_sorted(&stack[0], &stack[size]);
    }

    return stack;
}

vector<Score> GameManager::getScoresFromFile()
{
    ifstream inFile(FILENAME);

    vector<Score> scores;

    if (!inFile)
    {
        cerr << "Failed to open scores file." << endl;
        exit(-1);
    }
    else
    {
        string initials;
        int score;
        while (inFile >> initials >> score)
        {
            scores.push_back(Score(initials, score));
        }
    }
    return scores;
}

int GameManager::calculateScore()
{
    int n = numberOfPancakes;
    int diff = difficulty;
    const vector<int> &humanStack = leftPlayer->getStack();
    const vector<int> &aiStack = rightPlayer->getStack();
    bool humanStackSorted = is_sorted(humanStack.begin(), humanStack.end());
    bool aiStackSorted = is_sorted(aiStack.begin(), aiStack.end());
    if (aiStackSorted && !humanStackSorted)
    {
        return n;
    }
    if (aiStackSorted && humanStackSorted)
    {
        return n * (diff + 1);
    }
    return 2 * n * (diff + 1);
}

PlayerType GameManager::checkGameOver()
{
    const vector<int> &leftStack = leftPlayer->getStack();
    const vector<int> &rightStack = rightPlayer->getStack();
    bool leftSorted = is_sorted(leftStack.begin(), leftStack.end());
    bool rightSorted = is_sorted(rightStack.begin(), rightStack.end());

    if (leftSorted && rightSorted)
        return PlayerType::Both;
    if (leftSorted || rightSorted)
        return (leftSorted) ? PlayerType::LeftSide : PlayerType::RightSide;
    return PlayerType::Neither;
}

string GameManager::gameOver(PlayerType winner)
{
    string msg;
    switch (winner)
    {
    case PlayerType::LeftSide:
        msg = "You win!";
        break;
    case PlayerType::RightSide:
        msg = "The AI wins!";
        break;
    case PlayerType::Both:
        msg = "You tied with the AI!";
        break;
    default:
        msg = "No one wins!";
        break;
    }

    return msg;
}

bool GameManager::displayAndWriteFinalScore(int score, string message)
{
    vector<Score> scores = getScoresFromFile();
    ofstream outFile(FILENAME);

    scores.push_back(Score(playerInitials, score));
    sort(scores.begin(), scores.end(), [](Score &a, Score &b) { return a.score > b.score; });

    scores.resize(5);
    bool playAgain;
    EndGame endGameScreen(message, scores, &playAgain);
    if (!outFile)
    {
        cerr << "Failed to open scores file." << endl;
        exit(-1);
    }

    for (size_t j = 0; j < scores.size(); ++j)
    {
        Score e = scores[j];
        string i = e.initials;
        int s = e.score;
        outFile << i << " " << s << endl;
    }
    return playAgain;
}

void GameManager::makePlayers()
{
    if (leftPlayer != nullptr)
        delete leftPlayer;
    if (rightPlayer != nullptr)
        delete rightPlayer;

    numberOfPancakes = getNumberOfPancakes();
    difficulty = getAIDifficulty(numberOfPancakes);
    int *initialStack = getInitialStack(numberOfPancakes);

    // copy initial stack to vector
    vector<int> leftStack(&initialStack[0], &initialStack[numberOfPancakes]);
    // make a copy for the right player
    vector<int> rightStack = leftStack;

    leftPlayer = new HumanPlayer(leftStack, PlayerType::LeftSide, ioManager);
    rightPlayer = new AIPlayer(rightStack, PlayerType::RightSide, difficulty);

    delete[] initialStack;
}

PlayerType GameManager::nextTurn(PlayerType currentTurn)
{
    switch (currentTurn)
    {
    case PlayerType::LeftSide:
        return PlayerType::RightSide;
    case PlayerType::RightSide:
        return PlayerType::LeftSide;
    default:
        // should not reach this
        return PlayerType::Neither;
    }
}

Player *GameManager::getPlayer(PlayerType type)
{
    switch (type)
    {
    case PlayerType::LeftSide:
        return leftPlayer;
    case PlayerType::RightSide:
        return rightPlayer;
    default:
        // should not reach this
        return nullptr;
    }
}

PlayerType GameManager::gameLoop()
{
    PlayerType* winner = PlayerType::Neither;
    // Add window for main game

    return winner;
}

void GameManager::runGame()
{
    // Splash Screen

    // Setup screen
    bool userChoice = true;
    while (userChoice)
    {
        makePlayers();
        playerInitials = "AMS";

        PlayerType gameWinner = gameLoop();

        string message = gameOver(gameWinner);
        int score = calculateScore();
        userChoice = displayAndWriteFinalScore(score, message);
    }
}