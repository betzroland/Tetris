#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED
#include "Engine.h"

std::string intToString(int t);  // Just an auxiliary function. Converts an int type to string.

class Score{
public:
    int score;
    int highest;

    Score();    // Initializing score.

    void gameover_window(sf::RenderWindow& window);    // Displays "game over" and score.

    void score_count(Block* arrived, int& N, int& M, int& y_min, int& db); // Counting scores, and hiding the completed rows.

    void save_highest();    // Saves highest score.
};

#endif // SCORE_H_INCLUDED
