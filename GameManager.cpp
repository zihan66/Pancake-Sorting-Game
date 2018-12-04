#include <algorithm>
#include <chrono>
#include <exception>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>

#include "AIPlayer.h"
#include "GameData.h"
#include "GameManager.h"
#include "HumanPlayer.h"

#define SCORES "scores.txt"
#define GAMEDATA "setup.txt"
#define AISTACKS "AIpancake.txt"
#define HUMANSTACKS "pancake.txt"
#define MOVE "click.txt"
#define PLAYAGAIN "PlayAgain.txt"
#define OVER "GameOver.txt"

using namespace std;

GameManager::GameManager() : leftPlayer(0), rightPlayer(0) {}

GameManager::~GameManager()
{
    if (leftPlayer != 0)
        delete leftPlayer;
    if (rightPlayer != 0)
        delete rightPlayer;
}

vector<int> GameManager::getRandomInitialStack(int size)
{
    vector<int> stack;
    for (int i = 0; i < size; i++)
    {
        stack.push_back(i + 1);
    }

    bool sorted = true;
    while (sorted)
    {
        // get a random seed and use it in shuffle to randomize the array.
        random_shuffle(stack.begin(), stack.end());

        sorted = is_sorted(stack.begin(), stack.end());
    }

    return stack;
}

vector<Score> GameManager::getScoresFromFile()
{
    ifstream inFile(SCORES);

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

bool validateGameData(vector<string> lines, GameData &data)
{
    try
    {
        if (lines.size() < 4 || lines.size() > 5)
            return false;
        data.Initials = lines[0];
        data.StackHeight = stoi(lines[1]);
        data.AIDifficulty = stoi(lines[2]);
        data.IsRandom = (lines[3][0] == '1');
        if (data.IsRandom == false)
        {
            stringstream iss(lines[4]);
            int number;
            while (iss >> number)
            {
                data.Order.push_back(number);
            }
            if (data.Order.size() != data.StackHeight)
                return false;
        }
        return true;
    }
    catch (exception &e)
    {
        return false;
    }
}

GameData GameManager::getGameData(string filename)
{
    GameData ret;
    bool isValid = false;
    vector<string> lines;
    while (isValid == false)
    {
        ifstream gameDataFile(GAMEDATA);
        string line;
        lines.clear();
        while (getline(gameDataFile, line))
            lines.push_back(line);
        isValid = validateGameData(lines, ret);
        gameDataFile.close();
    }
    return ret;
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

void GameManager::writeFinalScore(int score)
{
    vector<Score> scores = getScoresFromFile();
    ofstream outFile(SCORES);

    scores.push_back(Score(playerInitials, score));
    sort(scores.begin(), scores.end(), [](Score &a, Score &b) { return a.score > b.score; });

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

    // Get Scores
    vector<Score> scores = getScoresFromFile();

    // inital data from file (JavaFX created)
    GameData gameData = getGameData(GAMEDATA);

    difficulty = gameData.AIDifficulty;
    numberOfPancakes = gameData.StackHeight;
    playerInitials = gameData.Initials;

    vector<int> order = (gameData.IsRandom) ? getRandomInitialStack(numberOfPancakes) : gameData.Order;

    vector<int> leftStack(order);
    // make a copy for the right player
    vector<int> rightStack = leftStack;

    leftPlayer = new HumanPlayer(leftStack, PlayerType::LeftSide);
    rightPlayer = new AIPlayer(rightStack, PlayerType::RightSide, difficulty);
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

void clearFile(string filename)
{
    ofstream file;
    file.open(filename, ofstream::out | ofstream::trunc);
}

void writeStackToFile(vector<int> stack, string filename)
{
    ofstream stackFile;
    stackFile.open(filename.c_str(), ofstream::out | ofstream::app);
    for (const auto &s : stack)
        stackFile << s << " ";
    stackFile << endl;
}

PlayerType GameManager::gameLoop()
{
    PlayerType winner = PlayerType::Neither;
    while (winner == PlayerType::Neither)
    {
        // To clear the file
        clearFile(HUMANSTACKS);
        clearFile(AISTACKS);

        writeStackToFile(leftPlayer->getStack(), HUMANSTACKS);
        writeStackToFile(rightPlayer->getStack(), AISTACKS);

        int playerMove = leftPlayer->getMove();
        int aiMove = rightPlayer->getMove();
        leftPlayer->executeMove(playerMove);
        rightPlayer->executeMove(aiMove);

        winner = checkGameOver();
    }

    return winner;
}

void setupFiles()
{
    ofstream gameData(GAMEDATA);
    gameData.close();
    ofstream over(OVER);
    over.close();
    ofstream ai(AISTACKS);
    ai.close();
    ofstream human(HUMANSTACKS);
    human.close();
    ofstream move(MOVE);
    move.close();
    ofstream aga(PLAYAGAIN);
    aga.close();
}

void writeMessage(string message)
{
    ofstream file(OVER);
    file << message;
}
bool getPlayAgain()
{
    int ret = -1;
    while (ret < 0)
    {
        ifstream moveFile(PLAYAGAIN);
        if (moveFile.peek() != ifstream::traits_type::eof())
            moveFile >> ret;

        moveFile.close();
    }
    return ret == 1;
}

void GameManager::runGame()
{
    bool userChoice = true;
    while (userChoice)
    {
        setupFiles();
        makePlayers();

        PlayerType gameWinner = gameLoop();
        string message = gameOver(gameWinner);
        int score = calculateScore();
        writeFinalScore(score);
        writeMessage(message);
        userChoice = getPlayAgain();
        cout << userChoice << endl;
    }

    remove(AISTACKS);
    remove(HUMANSTACKS);
    remove(MOVE);
    remove(GAMEDATA);
    remove(OVER);
    remove(PLAYAGAIN);
}
