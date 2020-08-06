#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
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
        arrived[i].x=-1;
        arrived[i].y=-1;
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
    for(int i=0; i<4; i++){
    if(block[0].y==(N-1) || block[1].y==(N-1) || block[2].y==(N-1) || block[3].y==(N-1) ){
        return true;
    }
        else return false;
    }
}

bool Engine::touch_block_y(){
    int a=0;
    if(db==0){return false;}
    else if(db>0){
        for(int i=0; i<4; i++){
            for(int j=0; j<db*4; j++){
                if(block[i].y==arrived[j].y-1 && block[i].x==arrived[j].x){
                    a=1;
                }
            }
        }
    }
    if(a==1){return true;}
    else return false;
}

bool Engine::touch_block_fromleft(){
    int a=0;
    if(db==0){return false;}
    else if(db>0){
        for(int i=0; i<4; i++){
            for(int j=0; j<db*4; j++){
                if(block[i].x==arrived[j].x-1 && block[i].y==arrived[j].y){
                    a=1;
                }
            }
        }
    }
    if(a==1){return true;}
    else return false;
}

bool Engine::touch_block_fromright(){
    int a=0;
    if(db==0){return false;}
    else if(db>0){
        for(int i=0; i<4; i++){
            for(int j=0; j<db*4; j++){
                if(block[i].x==arrived[j].x+1 && block[i].y==arrived[j].y){
                    a=1;
                }
            }
        }
    }
    if(a==1){return true;}
    else return false;
}

bool Engine::touch_wallfromleft(){
    int a=0;
    for(int i=0; i<4; i++){
        if(block[i].x==M-1){
            a=1;
        }
    }
    if(a==1){return true;}
    else return false;
}

bool Engine::touch_wallfromright(){
    int a=0;
    for(int i=0; i<4; i++){
        if(block[i].x==0){
            a=1;
        }
    }
    if(a==1){return true;}
    else return false;
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
    Block p;
    p.x=block[0].x;
    p.y=block[0].y;

    for(int i=1; i<4; i++){
        int x=block[i].y-p.y;
        int y=block[i].x-p.x;
        block[i].x=p.x-x;
        block[i].y=p.y+y;
    }

    int a=0;
    for(int j=1; j<4; j++){         //Withdraw rotation, if it would overlap with another block.
        for(int i=0; i<db*4; i++){
            if(block[j].x==arrived[i].x && block[j].y==arrived[i].y){
                a=1;
            }
        }
    }
    if(a==1){
        for(int j=1; j<4; j++){
            int x=block[j].y-p.y;
            int y=block[j].x-p.x;
            block[j].x=p.x+x;
            block[j].y=p.y-y;
        }
    }
    a=0;
    int r1=0;   int l1=0;   int r2=0;   int l2=0;
    for(int i=0; i<4; i++){
        if(block[i].x>M-1){
            r1=1;
        }
        if(block[i].x>M){
            r2=1;
        }
        if(block[i].x<0){
            l1=1;
        }
        if(block[i].x<-1){
            l2=1;
        }
    }
    if(r1==1){                      // Correction might be needed, if rotation happens directly beside walls.
        for(int i=0; i<4; i++){
            block[i].x=block[i].x-1;
        }
    }
    if(r2==1){                      // I block needs two steps of correction, if it is rotated directly beside the wall.
        for(int i=0; i<4; i++){
            block[i].x=block[i].x-1;
        }
    }
    if(l1==1){                      // Correction might be needed, if rotation happens directly beside walls.
        for(int i=0; i<4; i++){
            block[i].x=block[i].x+1;
        }
    }
    if(l2==1){                      // I block needs two steps of correction, if it is rotated directly beside the wall.
        for(int i=0; i<4; i++){
            block[i].x=block[i].x+1;
        }
    }
    r1=0;   l1=0;   r2=0;   l2=0;
    rotation=false;
    }
}

void Engine::move_block(){
    if (Keyboard::isKeyPressed(Keyboard::Right) && touch_block_fromleft()==false && touch_wallfromleft()==false){
        for(int i=0; i<4; i++){
            block[i].x=block[i].x+1;
        }
        sleep(milliseconds(100));
        }

    if (Keyboard::isKeyPressed(Keyboard::Left) && touch_block_fromright()==false && touch_wallfromright()==false){
        for(int i=0; i<4; i++){
            block[i].x=block[i].x-1;
        }
        sleep(milliseconds(100));
    }

    if(Keyboard::isKeyPressed(Keyboard::Down) && touch_bottom()==false && touch_block_y()==false){
        for(int i=0; i<4; i++){
            block[i].y=block[i].y+1;
        }
        sleep(milliseconds(50));
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
