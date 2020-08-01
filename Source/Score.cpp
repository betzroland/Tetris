#include <iostream>
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

string intToString(int t){
            string s;
            ostringstream out;
            out << t;
            s = out.str();
            return s;
        }

Score::Score(){ score=0; }

void Score::gameover_window(RenderWindow& window){
    window.clear();
    Text text1;
    Text text2;
    Text text3;

    Font font;
    font.loadFromFile("arial.ttf");

    text1.setFont(font);
    text2.setFont(font);
    text3.setFont(font);

    text1.setString("Game over!");
    text2.setString("Score: "+intToString(score));

    ifstream file;
    file.open("highest.txt");
    file >> highest;
    file.close();

    text3.setString("Highest score: "+intToString(highest));

    text1.setCharacterSize(24);
    text2.setCharacterSize(24);
    text3.setCharacterSize(24);

    text1.setFillColor(Color::Green);
    text2.setFillColor(Color::Green);
    text3.setFillColor(Color::Green);

    text1.setStyle(Text::Bold);
    text2.setStyle(Text::Bold);
    text3.setStyle(Text::Bold);

    text1.setPosition(50, 120);
    text2.setPosition(70, 160);
    text3.setPosition(30, 200);

    window.draw(text1);
    window.draw(text2);
    window.draw(text3);

    window.display();
}

void Score::score_count(Block* arrived, int& N, int& M, int& y_min, int& db){
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
