#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED
#include "Engine.h"
#include "Score.h"

class Draw{
public:
    int pixel;
    sf::Texture texture1, texture2;
    sf::Sprite sprite1, sprite2, sprite3;
    bool start;

    Draw();

    void set_BlockColor(int* color, const int db);

    void draw_field(const Engine& engine, sf::RenderWindow& window);

    void draw_blocks(Engine& engine, sf::RenderWindow& window);

    void draw_openingwindow(sf::RenderWindow& window);

    void draw_gameover(sf::RenderWindow& window, Score& scr);

};


#endif // DRAW_H_INCLUDED
