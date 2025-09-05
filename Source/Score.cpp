#include "../Headers/Score.h"
#include <fstream>
#include <cstdio>
#include <vector>

//function used to store bestMoves per level
std::vector<ScoreEntry> loadScores(std::size_t nLevels, const std::string& path) { // pass in the amount of levels in the game and the path of where we are storing the data
    std::vector<ScoreEntry> scores(nLevels); // creates  a vector of schors of n level size;
    //looks somthing like this: {best move} {best move} {best move} {best move} {best move}
    
    std::ifstream inFile(path); // uses input stream decares inFile as variable and tries to open path ("scores.txt)
    if (!inFile) return scores; // if we cant open the file return

    // for loop to input moves per level
    for (std::size_t i = 0; i < nLevels; ++i) {
        int moves; // create a new temp move counter per each level
        if (inFile >> moves) { // will try to inptut move to the file if moves is a number
            if (moves >= 0) scores[i].bestMoves = moves; // if the moves is not negative then it updates the best move at the current level scores[i].bestMove
        }
        else { // break out of the loop
            break;
        }
    }
    return scores; // return the new vector of bestMoves per each level
}

// function used to save the scores
void saveScores(const std::vector<ScoreEntry>& scores, const std::string& path) { // pass in a vector of scores of type ScoreEntry, and path where we will be storing the data
    
    //ofstream (used to write into file) 
    // write into path "scores.txt" and clears it (truncates to empty) before writing
    std::ofstream outFile(path, std::ios::trunc);

    // loop through the scores 
    // for each entry in vector of scores
    for (const auto& entry : scores) {
        //moves is set to -1 if .bestMoves is equal to std::numeric_limits<int>::max()) or to the entries.bestMoves
        int moves = (entry.bestMoves == std::numeric_limits<int>::max()) ? -1 : entry.bestMoves;
        outFile << moves << std::endl; // print to file and end line
    }
}