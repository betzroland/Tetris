#include <SFML/Graphics.hpp>
#include "Engine.h"

using namespace std;
using namespace sf;

Engine::Engine(){
    M=10;   N=20;
    db=0;
    y_min=N-1;
    rotation=false;
    for(int i=0; i<250; i++){
        color[i]=-1;
    }
    for(int i=0; i<1000; i++){
        arrived[i].x=i;
        arrived[i].y=N+1;
    }
}

void Engine::set_blockshape(){
    int shapes_x[7][4]={    // Array for defining blocks (x coordinates).
            0,0,0,0,    // I
            1,0,0,1,    // O
            0,0,1,0,    // T
            0,0,0,1,    // L
            1,1,1,0,    // J
            0,0,1,1,    // S
            1,1,0,0     // Z
    };

    int shapes_y[7][4]={    // Array for defining blocks (y coordinates).
            1,0,2,3,    // I
            0,0,1,1,    // O
            1,0,1,2,    // T
            1,0,2,2,    // L
            1,0,2,2,    // J
            1,0,1,2,    // S
            1,0,1,2     // Z
    };

    for(int i=0; i<4; i++){
        block[i].x=shapes_x[color[db]][i]+(M/2)-1;
        block[i].y=shapes_y[color[db]][i]-1;
    }
}

bool Engine::touch_bottom(){
    if(block[0].y==(N-1) || block[1].y==(N-1) || block[2].y==(N-1) || block[3].y==(N-1) ){
        return true;
    }
    else{
        for(int i=0; i<4; i++){
            for(int j=0; j<db*4; j++){
                if(block[i].y==arrived[j].y-1 && block[i].x==arrived[j].x){
                    return true;
                }
            }
        }
    }
    return false;
}

bool Engine::is_gameover(){
     for(int i=0; i<db*4; i++){
        if((block[2].y==arrived[i].y && block[2].x==arrived[i].x) || (block[3].y==arrived[i].y && block[3].x==arrived[i].x)){
            return true;
        }
     }
     return false;
}

void Engine::rotate_block(){
    if(rotation==true && color[db]!=1){

    for(int i=0; i<4; i++){
        block_copy[i]=block[i];
    }

    for(int i=1; i<4; i++){             // rotate
        int x=block[i].y-block[0].y;
        int y=block[i].x-block[0].x;
        block[i].x=block[0].x-x;
        block[i].y=block[0].y+y;
    }

    if(Engine::is_overlap()){
        for(int i=0; i<4; i++){
            block[i]=block_copy[i];
        }
    }
    rotation=false;
    }
}

void Engine::move_block(float& delay){

    for(int i=0; i<4; i++){
        block_copy[i]=block[i];
    }

    if (Keyboard::isKeyPressed(Keyboard::Right)){
        for(int i=0; i<4; i++){
            block[i].x=block[i].x+1;
        }
    sleep(milliseconds(125));
    }

    else if (Keyboard::isKeyPressed(Keyboard::Left)){
        for(int i=0; i<4; i++){
            block[i].x=block[i].x-1;
        }
    sleep(milliseconds(125));
    }

    else if(Keyboard::isKeyPressed(Keyboard::Down)){
        delay=0.05;
    }
    else{ delay=0.3; }

    if(Engine::is_overlap()){
        for(int i=0; i<4; i++){
            block[i]=block_copy[i];
        }
    }
}

void Engine::attach_block(){
    for(int i=(db*4); i<((db+1)*4); i++){
        arrived[i].x=block[(i%4)].x;
        arrived[i].y=block[(i%4)].y;
        if(arrived[i].y<y_min){
            y_min=arrived[i].y;
        }
    }
db=db+1;
}

bool Engine::is_overlap(){
    for(int j=1; j<4; j++){
        for(int i=0; i<db*4; i++){
            if(block[j].x==arrived[i].x && block[j].y==arrived[i].y){
                return true;
            }
        }
    }
    for(int i=0; i<4; i++){
        if(block[i].x==-1 || block[i].x==M){
            return true;
        }
    }
return false;
}
