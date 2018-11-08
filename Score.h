#pragma once

#include <string>

struct Score {
public:
  std::string initials;
  int score;
  
  Score() {}
Score(const std::string& initials, int score)
    : initials(initials), score(score) {}

  inline bool operator() (const Score& s1, const Score& s2)
  {
    return (s1.score > s2.score);
  }
};
