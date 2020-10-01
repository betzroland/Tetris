#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED
#include "Engine.h"

class Score{
public:
    int score;
    int highest;

    Score();

    void score_count(Engine& engine);

    void save_highest();
};

#endif // SCORE_H_INCLUDED
