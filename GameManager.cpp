#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

#include <curses.h>

#include "GameManager.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"

#include "EndGame.h"

#define FILENAME "scores"

using namespace std;

GameManager::GameManager() : leftPlayer(0), rightPlayer(0)
{
    ioManager = new IOManager();
}

GameManager::~GameManager()
{
    delete ioManager;
    if (leftPlayer != 0)
        delete leftPlayer;
    if (rightPlayer != 0)
        delete rightPlayer;
}

int GameManager::getNumberOfPancakes()
{
    return ioManager->promptForNumber("Enter the number of pancakes (2-9): ", 2, 9);
}

int GameManager::getAIDifficulty(int maxDifficulty)
{
    ostringstream ss;
    ss << "Enter a number for the AI difficulty (1-" << maxDifficulty << "): ";

    return ioManager->promptForNumber(ss.str(), 1, maxDifficulty);
}

template <class TElement>
void printArray(ostream &os, TElement *array, int size, int i)
{
    os << "[";
    for (int j = 0; j < size; j++)
    {
        if (j > 0)
            os << ", ";

        if (j < i)
            os << array[j];
        else
        {
            os << "_";
        }
    }
    os << "]";
}

int *GameManager::promptForInitialStack(int size)
{
    int *stack = new int[size];
    int i = 0;
    while (i < size)
    {
        ostringstream ss;
        printArray(ss, stack, size, i);
        ss << endl
           << "Please input pancake #" << i << " (1-" << size << "): ";
        int input = ioManager->promptForNumber(ss.str(), 1, size);

        // ensure the values aren't repeated
        if (find(&stack[0], &stack[i], input) != &stack[i])
        {
            beep();
            continue;
        }
        stack[i] = input;
        i++;

        // make sure array isn't already sorted
        if (i == size && is_sorted(&stack[0], &stack[size]))
        {
            ioManager->displayMessage("Given pancake stack is already sorted.");
            i = 0;
        }
    }
    return stack;
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

int *GameManager::getInitialStack(int size)
{
    bool manual = ioManager->promptYesNo("Do you want to enter the initial stack manually? (y/n): ");
    if (manual)
    {
        return promptForInitialStack(size);
    }
    else
    {
        return getRandomInitialStack(size);
    }
}

string GameManager::promptForInitials()
{
    return ioManager->prompt("Enter your initials: ");
}

void GameManager::displayScores(string initials)
{
    vector<Score> scores = getScoresFromFile();
    sort(scores.begin(), scores.end(), Score());
    if (scores.size() > 5)
    {
        vector<Score> sub(scores.begin(), scores.begin() + 5);
        sub.push_back(Score(initials, 0));
        ioManager->displayScores(sub);
    }
    else
    {
        scores.push_back(Score(initials, 0));
        ioManager->displayScores(scores);
    }
}

void GameManager::displaySplash()
{
    ioManager->showSplashScreen();
}

void GameManager::displayInstructions()
{
    ioManager->displayInstructions();
}

int GameManager::calculateScore()
{
    int n = numberOfPancakes;
    int diff = difficulty;
    const std::vector<int> &humanStack = leftPlayer->getStack();
    const std::vector<int> &aiStack = rightPlayer->getStack();
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
    const std::vector<int> &leftStack = leftPlayer->getStack();
    const std::vector<int> &rightStack = rightPlayer->getStack();
    bool leftSorted = is_sorted(leftStack.begin(), leftStack.end());
    bool rightSorted = is_sorted(rightStack.begin(), rightStack.end());

    if (leftSorted && rightSorted)
        return PlayerType::Both;
    if (leftSorted || rightSorted)
        return (leftSorted) ? PlayerType::LeftSide : PlayerType::RightSide;
    return PlayerType::None;
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

    return string;
}

void GameManager::displayAndWriteFinalScore(int score, string message)
{
    vector<Score> scores = getScoresFromFile();
    ofstream outFile(FILENAME);

    scores.push_back(Score(playerInitials, score));
    sort(scores.begin(), scores.end(), [](Score &a, Score &b) { return a.score > b.score; });

    bool playAgain;
    ioManager->displayEndGameScreen(message, scores, e.initials, &playAgain);

    scores.resize(5);

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
        return PlayerType::None;
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

void GameManager::initScreen()
{
    initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    noecho();
    curs_set(0);
    keypad(stdscr, true);
}

PlayerType GameManager::gameLoop()
{
    PlayerType winner = PlayerType::None;
    while (winner == PlayerType::None)
    {
        ioManager->drawStacks(leftPlayer, rightPlayer);

        // Player move
        int playerMove = leftPlayer->getMove();
        ioManager->blinkPancakes(playerMove, leftPlayer);
        leftPlayer->executeMove(playerMove);

        ioManager->drawStacks(leftPlayer, rightPlayer);

        // AI move
        if (difficulty > 5)
            ioManager->drawAIThinking(numberOfPancakes, difficulty);
        int aiMove = rightPlayer->getMove();
        ioManager->blinkPancakes(aiMove, rightPlayer);
        rightPlayer->executeMove(aiMove);

        winner = checkGameOver();
    }

    return winner;
}

void GameManager::runGame()
{
    initScreen();
    displaySplash();
    displayInstructions();

    bool userChoice = true;
    while (userChoice)
    {
        makePlayers();
        playerInitials = promptForInitials();
        displayScores(playerInitials);

        PlayerType gameWinner = gameLoop();

        string message = gameOver(gameWinner);
        int score = calculateScore();
        displayAndWriteFinalScore(score, message);

        userChoice = promptToPlayAgain();
    }

    endwin();
}
