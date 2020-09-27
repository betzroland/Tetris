#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED
#include "Engine.h"

class Score{
public:
    int score;
    int highest;

    Score();    // Initializing score.

    void score_count(Engine& engine); // Counting scores, and hiding the completed rows.

    void save_highest();    // Saves highest score.
};

#endif // SCORE_H_INCLUDED
