#ifndef SCORE_H
#define SCORE_H
#include <vector>
#include <string>
#include <limits> 

struct ScoreEntry {
    int bestMoves = std::numeric_limits<int>::max();
};

std::vector<ScoreEntry> loadScores(std::size_t nLevels, const std::string& path);
void saveScores(const std::vector<ScoreEntry>& scores, const std::string& path);



#endif //SCORE_H