#pragma once

struct Score
{
  public:
    string initials;
    int score;

    Score(): initials("N/A"), score(0){}
    Score(const string &initials, int score)
        : initials(initials), score(score) {}

    inline bool operator()(const Score &s1, const Score &s2)
    {
        return (s1.score > s2.score);
    }

    string getText() {
        return initials + " " + to_string(score);
    }
};
