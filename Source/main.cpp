#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <time.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
using namespace sf;

Event event;
int pixel=27;
int M=10;   int N=20;
int counter=0;
int row;
int db=0;
int y_min=N-1;
int score=0;
int rowcounter=0;
bool rotator=false;
int h;
bool gameover=false;

vector<int> color(100,-1);  // Stores the colors of the created blocks.

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

class Block{
    public:
        int x, y;
};

Block block[4];         // Stores the coordinates of one block.
Block arrived[1000];    // Stores the coordinates of all the placed blocks.

string intToString(int t);  // Converts an integer into string.

bool touch_bottom(Block* block);    // Detects whether a block has touched the bottom of the Tetris-field or not.

bool touch_block_y(Block* block, Block* arrived, int& db);  // Detects whether an arriving block has reached a placed block or not.

bool touch_block_fromleft(Block* block, Block* arrived, int& db); // Detects whether a block has touched a placed block from left side or not.

bool touch_block_fromright(Block* block, Block* arrived, int& db);  // Detects whether a block has touched a placed block from right side or not.

bool touch_wallfromleft(Block* block);      // Detects whether a block has touched the wall from left side or not.

bool touch_wallfromright(Block* block);     // Detects whether a block has touched the wall from right side or not.

void rotation(Block* block, int& n, Block* arrived);    // Function for rotating a block.

//--------------------------------------------------------------------------//

int main()
{
    int index[M]={-1};

    for(int i=0; i<1000; i++){
    arrived[i].x=-1;
    arrived[i].y=-1;
    }

    srand(time(NULL));
    Texture texture;
    texture.loadFromFile("tiles.png");
    Sprite sprite(texture);

    Texture texture2;
    texture2.loadFromFile("grid.png");
    Sprite sprite2(texture2);

    Sprite sprite3(texture);

    RenderWindow window(VideoMode(M*pixel, N*pixel), "Tetris");

    float timer=0;
    float delay=0.3;
    Clock clock;
    int n;

    while(window.isOpen()){

        n=rand()%7;
        color[db]=n;

        sprite.setTextureRect(sf::IntRect(color[db]*pixel, 0, pixel, pixel));

        for(int i=0; i<4; i++){
                block[i].x=shapes_x[n][i]+(M/2)-1;
                block[i].y=shapes_y[n][i]-1;
        }

        for(int i=0; i<db*4; i++){
            if((block[2].y==arrived[i].y && block[2].x==arrived[i].x) || (block[3].y==arrived[i].y && block[3].x==arrived[i].x)){
                gameover=true;
                sleep(milliseconds(1000));
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
                file >> h;
                file.close();

                text3.setString("Highest score: "+intToString(h));

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
        }

        if(gameover){
            sleep(milliseconds(4000));
            window.close();
        }

        while(touch_bottom(block)==false && touch_block_y(block, arrived, db)==false){
            float time=clock.getElapsedTime().asSeconds();
            clock.restart();
            timer=timer+time;

            if(timer>delay){
                for(int i=0; i<4; i++){
                    block[i].y=block[i].y+1;
                }
            timer=0;
            }

            for (int i=0; i<M; i++){
                for (int j=0; j<N; j++){
                    sprite2.setPosition(i*pixel, j*pixel);
                    window.draw(sprite2);
                }
            }

            for(int i=0; i<4; i++){
                sprite.setPosition(block[i].x*pixel, block[i].y*pixel);
                window.draw(sprite);
            }

            for(int i=0; i<db*4; i++){
                sprite3.setTextureRect(sf::IntRect(color[i/4]*pixel, 0, pixel, pixel));
                sprite3.setPosition(arrived[i].x*pixel, arrived[i].y*pixel);
                window.draw(sprite3);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && touch_block_fromleft(block, arrived, db)==false && touch_wallfromleft(block)==false){
                for(int i=0; i<4; i++){
                    block[i].x=block[i].x+1;
                }
                sleep(milliseconds(90));
                }

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && touch_block_fromright(block, arrived, db)==false && touch_wallfromright(block)==false){
                for(int i=0; i<4; i++){
                    block[i].x=block[i].x-1;
                }
                sleep(milliseconds(90));
            }

            while(window.pollEvent(event)){
                if(event.type==Event::Closed){
                    window.close();
                }
                else if(event.type==Event::KeyPressed){
                    if(event.key.code==Keyboard::Up){
                        rotator=true;
                    }
                }
            }

            int r1=0;   int l1=0;   int r2=0;   int l2=0;
            if(rotator==true && n!=1){
                rotation(block, n, arrived);
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
                if(r1==1){
                    for(int i=0; i<4; i++){
                        block[i].x=block[i].x-1;
                    }
                }
                if(r2==1){                      //I blokknak kétszeri eltolás kell, ha a falak mellett forgatunk
                    for(int i=0; i<4; i++){
                        block[i].x=block[i].x-1;
                    }
                }
                if(l1==1){
                    for(int i=0; i<4; i++){
                        block[i].x=block[i].x+1;
                    }
                }
                if(l2==1){                      //I blokknak -||-
                    for(int i=0; i<4; i++){
                        block[i].x=block[i].x+1;
                    }
                }
            }
            r1=0;   l1=0;   r2=0;   l2=0;
            rotator=false;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && touch_bottom(block)==false && touch_block_y(block, arrived, db)==false){
                for(int i=0; i<4; i++){
                    block[i].y=block[i].y+1;
                }
                sleep(milliseconds(45));
                }

            window.display();
        }

        for(int i=(db*4); i<((db+1)*4); i++){
            arrived[i].x=block[(i%4)].x;
            arrived[i].y=block[(i%4)].y;
            if(arrived[i].y<y_min){
                y_min=arrived[i].y;
            }
            }

        db=db+1;

        for(int i=0; i<M; i++){
            index[i]={-1};
            }

        row=N-1;

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

    if(gameover){
            if(score>h){
            ofstream file;
                file.open("highest.txt");
                file << score;
                file.close();
            }
    }

return 0;
}

//----------------------------------------------------------//

string intToString(int t){
            string s;
            ostringstream out;
            out << t;
            s = out.str();
            return s;
        }


bool touch_bottom(Block* block){
        for(int i=0; i<4; i++){
        if(block[0].y==(N-1) || block[1].y==(N-1) || block[2].y==(N-1) || block[3].y==(N-1) ){
            return true;
        }
            else return false;
        }
}

bool touch_block_y(Block* block, Block* arrived, int& db){
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

bool touch_block_fromleft(Block* block, Block* arrived, int& db){
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

bool touch_block_fromright(Block* block, Block* arrived, int& db){
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

bool touch_wallfromleft(Block* block){
        int a=0;
        for(int i=0; i<4; i++){
            if(block[i].x==M-1){
                a=1;
            }
        }
        if(a==1){return true;}
        else return false;
}

bool touch_wallfromright(Block* block){
        int a=0;
        for(int i=0; i<4; i++){
            if(block[i].x==0){
                a=1;
            }
        }
        if(a==1){return true;}
        else return false;
}

void rotation(Block* block, int& n, Block* arrived){
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
        for(int j=1; j<4; j++){         //Ha egy már lerakott blokkba ütközne, visszavonja a forgatást.
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
        }
