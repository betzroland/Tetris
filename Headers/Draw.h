#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED
#include "Engine.h"

using namespace std;
using namespace sf;

class Draw{
public:
    int pixel;
    Texture texture1, texture2;
    Sprite sprite1, sprite2, sprite3;
    bool start;

    Draw(); // Initializing class variables.

    void set_BlockColor(int* color, int& db);   // Sets the color of a new block.

    void draw_field(int& M, int& N, RenderWindow& window);  // Drawing tetris field.

    void draw_blocks(Block* block, int* color, Block* arrived, RenderWindow& window, int& db);  // Drawing blocks.

    void draw_openingwindow(RenderWindow& window);  // Opening window when game is starting.
};


#endif // DRAW_H_INCLUDED