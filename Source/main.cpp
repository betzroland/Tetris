#include <iostream>
#include <time.h>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Draw.h"
#include "Score.h"
#include "Engine.h"

using namespace std;
using namespace sf;

int main()
{
    srand(time(NULL));

    Engine engine;
    Draw draw;
    Score scr;
    Event event;

    Texture texture1;
    texture1.loadFromFile("tiles.png");
    Sprite sprite1(texture1);

    Texture texture2;
    texture2.loadFromFile("grid.png");
    Sprite sprite2(texture2);

    Sprite sprite3(texture1);

    RenderWindow window(VideoMode(engine.M*draw.pixel, engine.N*draw.pixel), "Tetris");

    float timer=0;
    float delay=0.3;
    Clock clock;

    while(window.isOpen()){

        engine.color[engine.db]=rand()%7;

        draw.set_BlockColor(engine.color, engine.db, sprite1);

        engine.set_blockshape();

        //Ezt még beírhatod egy bool gameover függvénybe.
        for(int i=0; i<engine.db*4; i++){
            if((engine.block[2].y==engine.arrived[i].y && engine.block[2].x==engine.arrived[i].x) || (engine.block[3].y==engine.arrived[i].y && engine.block[3].x==engine.arrived[i].x)){
                engine.gameover=true;
                sleep(milliseconds(1000));
                scr.gameover_window(window);
            }
        }

        if(engine.gameover){
            sleep(milliseconds(3000));
            window.close();
        }

        while(engine.touch_bottom()==false && engine.touch_block_y()==false){
            float time=clock.getElapsedTime().asSeconds();
            clock.restart();
            timer=timer+time;

            if(timer>delay){
                for(int i=0; i<4; i++){
                    engine.block[i].y=engine.block[i].y+1;
                }
            timer=0;
            }

            draw.draw_field(engine.M, engine.N, window, sprite2);
            draw.draw_blocks(engine.block, engine.color, engine.arrived, window, engine.db, sprite1, sprite3);

            if (Keyboard::isKeyPressed(Keyboard::Right) && engine.touch_block_fromleft()==false && engine.touch_wallfromleft()==false){
                for(int i=0; i<4; i++){
                    engine.block[i].x=engine.block[i].x+1;
                }
                sleep(milliseconds(90));
                }

            if (Keyboard::isKeyPressed(Keyboard::Left) && engine.touch_block_fromright()==false && engine.touch_wallfromright()==false){
                for(int i=0; i<4; i++){
                    engine.block[i].x=engine.block[i].x-1;
                }
                sleep(milliseconds(90));
            }

            if(Keyboard::isKeyPressed(Keyboard::Down) && engine.touch_bottom()==false && engine.touch_block_y()==false){
                for(int i=0; i<4; i++){
                    engine.block[i].y=engine.block[i].y+1;
                }
                sleep(milliseconds(45));
                }

            while(window.pollEvent(event)){
                if(event.type==Event::Closed){
                    window.close();
                }
                if(event.type==Event::KeyPressed){
                    if(event.key.code==Keyboard::Up){
                        engine.rotator=true;
                    }
                }
            }
            if(engine.rotator==true && engine.color[engine.db]!=1){
                engine.rotation();
            }
            engine.rotator=false;

            window.display();
        }

        engine.attach_block();

        scr.score_count(engine.arrived, engine.N, engine.M, engine.y_min, engine.db);
    }
    scr.save_highest();

return 0;
}
