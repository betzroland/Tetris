#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Draw.h"
#include "Score.h"
#include "Engine.h"

using namespace std;
using namespace sf;

Draw::Draw(){
    pixel=27;
}

void Draw::set_BlockColor(int* color, int& db, Sprite& sprite1){
    sprite1.setTextureRect(IntRect(color[db]*pixel, 0, pixel, pixel));
}

void Draw::draw_field(int& M, int& N, RenderWindow& window, Sprite& sprite2){
    for (int i=0; i<M; i++){
        for (int j=0; j<N; j++){
            sprite2.setPosition(i*pixel, j*pixel);
            window.draw(sprite2);
        }
    }
}

void Draw::draw_blocks(Block* block, int* color, Block* arrived, RenderWindow& window, int& db, Sprite& sprite1, Sprite& sprite3){
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


