#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Draw.h"
#include "Score.h"

using namespace std;
using namespace sf;

Draw::Draw(){
    texture1.loadFromFile("tiles.png");
    sprite1.setTexture(texture1);

    texture2.loadFromFile("grid.png");
    sprite2.setTexture(texture2);

    sprite3.setTexture(texture1);

    pixel=27;
    start=true;
}

void Draw::set_BlockColor(int* color, int& db){
    sprite1.setTextureRect(IntRect(color[db]*pixel, 0, pixel, pixel));
}

void Draw::draw_field(int& M, int& N, RenderWindow& window){
    for (int i=0; i<M; i++){
        for (int j=0; j<N; j++){
            sprite2.setPosition(i*pixel, j*pixel);
            window.draw(sprite2);
        }
    }
}

void Draw::draw_blocks(Block* block, int* color, Block* arrived, RenderWindow& window, int& db){
    //draw falling block
    for(int i=0; i<4; i++){
        sprite1.setPosition(block[i].x*pixel, block[i].y*pixel);
        window.draw(sprite1);
    }

    //draw arrived blocks
    for(int i=0; i<db*4; i++){
        sprite3.setTextureRect(IntRect(color[i/4]*pixel, 0, pixel, pixel));
        sprite3.setPosition(arrived[i].x*pixel, arrived[i].y*pixel);
        window.draw(sprite3);
    }
}

void Draw::draw_openingwindow(RenderWindow& window){
    int seconds;
    Text text1;
    Text text2;
    Text text3;

    Font font;
    font.loadFromFile("arial.ttf");

    text1.setFont(font);
    text2.setFont(font);
    text3.setFont(font);

    text1.setCharacterSize(24);
    text2.setCharacterSize(24);
    text3.setCharacterSize(24);

    text1.setFillColor(Color::Green);
    text2.setFillColor(Color::Green);
    text3.setFillColor(Color::Green);

    text1.setStyle(Text::Bold);
    text2.setStyle(Text::Bold);
    text3.setStyle(Text::Bold);

    text1.setPosition(45, 120);
    text2.setPosition(125, 160);
    text3.setPosition(80, 200);

    for(int i=3; i>=0; i--){
    seconds=i;
    text1.setString("Game starts in");
    text2.setString(intToString(seconds));
    text3.setString("seconds!");

    window.draw(text1);
    window.draw(text2);
    window.draw(text3);

    window.display();
    sleep(milliseconds(1000));
    window.clear();
    }

    start=false;
    window.clear();
}


