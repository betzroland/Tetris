#include <time.h>
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

RenderWindow window(VideoMode(engine.M*draw.pixel, engine.N*draw.pixel), "Tetris");

float timer=0;
float delay=0.3;
Clock clock;

while(window.isOpen()){

    if(draw.start==true){
        draw.draw_openingwindow(window);
    }
    else{

        engine.color[engine.db]=rand()%7;

        draw.set_BlockColor(engine.color, engine.db);

        engine.set_blockshape();

        if(engine.is_gameover()){
            scr.gameover_window(window);
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

            draw.draw_field(engine.M, engine.N, window);
            draw.draw_blocks(engine.block, engine.color, engine.arrived, window, engine.db);

            while(window.pollEvent(event)){
                if(event.type==Event::Closed){
                    window.close();
                }
                if(event.type==Event::KeyPressed){
                    if(event.key.code==Keyboard::Up){
                        engine.rotation=true;
                    }
                }
            }

            engine.rotate_block();

            engine.move_block();

            window.display();
        }

        engine.attach_block();

        scr.score_count(engine.arrived, engine.N, engine.M, engine.y_min, engine.db);
    }
}

scr.save_highest();

return 0;
}
