#include <fstream>
#include <SFML/Graphics.hpp>
#include "Score.h"

using namespace std;
using namespace sf;

Score::Score(){ score=0; }

void Score::score_count(Engine& engine){
    int index[engine.M];
    for(int i=0; i<engine.M; i++){
            index[i]={-1};
            }
    int row=engine.N-1;
    int counter=0;
    int rowcounter=0;

    for(int i=row; i>=engine.y_min; i--){
        for(int j=0; j<engine.db*4; j++){
            if(engine.arrived[j].y==i){
                counter++;
            }
        }
        if(counter==engine.M){
            rowcounter++;
            counter=0;
        }
        else counter=0;
    }
    if(rowcounter==1){
        score=score+10;
    }
    if(rowcounter==2){
        score=score+30;
    }
    if(rowcounter==3){
        score=score+50;
    }
    if(rowcounter==4){
        score=score+70;
    }
    rowcounter=0;

    while(row>=engine.y_min){
        for(int i=0; i<engine.db*4; i++){
            if(engine.arrived[i].y==row){
                index[counter]=i;
                counter++;
            }
        }
        if(counter==engine.M){
            for(int i=0; i<engine.M; i++){
                engine.arrived[index[i]].y=engine.arrived[index[i]].y+20;
            }
            for(int i=0; i<engine.db*4; i++){
                if(engine.arrived[i].y<row){
                engine.arrived[i].y=engine.arrived[i].y+1;
                }
            }
            row=row;
            engine.y_min=engine.y_min+1;
        }
        else {row=row-1;}
        counter=0;
    }
}

void Score::save_highest(){
    if(score>highest){
        ofstream file;
        file.open("highest.txt");
        file << score;
        file.close();
    }
}
