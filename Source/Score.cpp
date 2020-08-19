#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Score.h"

using namespace std;
using namespace sf;

Score::Score(){ score=0; }

void Score::score_count(Block* arrived, const int N, const int M, int& y_min, const int db){
    int index[M];
    for(int i=0; i<M; i++){
            index[i]={-1};
            }
    int row=N-1;
    int counter=0;
    int rowcounter=0;

    for(int i=row; i>=y_min; i--){
        for(int j=0; j<db*4; j++){
            if(arrived[j].y==i){
                counter++;
            }
        }
        if(counter==M){
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

    while(row>=y_min){
        for(int i=0; i<db*4; i++){
            if(arrived[i].y==row){
                index[counter]=i;
                counter++;
            }
        }
        if(counter==M){
            for(int l=0; l<M; l++){
                arrived[index[l]].y=arrived[index[l]].y+20;
            }
            for(int h=0; h<db*4; h++){
                if(arrived[h].y<row){
                arrived[h].y=arrived[h].y+1;
                }
            }
            row=row;
            y_min=y_min+1;
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
