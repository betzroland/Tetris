#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED
#include "Engine.h"

class Draw{
public:
    int pixel;
    sf::Texture texture1, texture2;
    sf::Sprite sprite1, sprite2, sprite3;
    bool start;

    Draw(); // Initializing class variables.

    void set_BlockColor(int* color, const int db);   // Sets the color of a new block.

    void draw_field(const int M, const int N, sf::RenderWindow& window);  // Drawing tetris field.

    void draw_blocks(Block* block, int* color, Block* arrived, sf::RenderWindow& window, const int db);  // Drawing blocks.

    void draw_openingwindow(sf::RenderWindow& window);  // Opening window when game is starting.

    void draw_gameover(sf::RenderWindow& window, const int score, int& highest);    // Drawing game over screen.

};


#endif // DRAW_H_INCLUDED
