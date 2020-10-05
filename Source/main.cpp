#include <time.h>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

const int height=20; const int width=10;
const int pixel=27;
int field[height][width];
int score;

struct Block{
    int x, y;
};
Block block[4];

Text line1, line2, line3;    Font font;
Texture texture_of_tiles, texture_of_field;
Sprite sprite_of_block, sprite_of_field, sprite_of_fallenblocks;

int shapes_x[7][4]={    // Array for defining the shape of blocks (x coordinates).
            0,0,0,0,    // I
            1,0,0,1,    // O
            0,0,1,0,    // T
            0,0,0,1,    // L
            1,1,1,0,    // J
            0,0,1,1,    // S
            1,1,0,0     // Z
    };

int shapes_y[7][4]={    // Array for defining the shape of blocks (y coordinates).
            1,0,2,3,    // I
            0,0,1,1,    // O
            1,0,1,2,    // T
            1,0,2,2,    // L
            1,0,2,2,    // J
            1,0,1,2,    // S
            1,0,1,2     // Z
    };

void initialize_draw_variables();   //draw_variables: texts, textures and sprites

void draw_openingwindow(RenderWindow& window);

void initialize_field();

void set_new_block(const int color);

bool is_gameover();

void draw_gameoverwindow(RenderWindow& window);

void stepping_block_downward();

bool is_bottom_reached();

void make_blockcopy(Block* copy);

void rotate_block(bool& rotation, const int color);

void move_block_horizontally(int& dx);

bool is_overlap();

void withdraw_previous_move(Block* copy);

void draw_field(RenderWindow& window);

void draw_block(RenderWindow& window);

void attach_fallen_block(const int color);

void clear_filled_rows();


int main()
{
    srand(time(NULL));

    initialize_draw_variables();

    initialize_field();

    RenderWindow window(VideoMode(width*pixel, height*pixel), "Tetris");

    draw_openingwindow(window);

    while(window.isOpen()){

        int color=rand()%7+1;

        set_new_block(color);

        if(is_gameover()){
            draw_gameoverwindow(window);
        }

        Clock clock;    float timer=0;    float delay=0.3;
        while(!is_bottom_reached()){

            Block copy[4];        // "safety copy" in case the block would overlap after making a move
            make_blockcopy(copy);

            float time=clock.getElapsedTime().asSeconds();
            clock.restart();
            timer=timer+time;

            if(timer>delay){
                stepping_block_downward();
                timer=0;
            }

            Event event;    bool rotation=false;    int dx=0;
            while(window.pollEvent(event)){
                if(event.type==Event::Closed){
                    window.close();
                }
                if(event.type==Event::KeyPressed){
                    if(event.key.code==Keyboard::Up) rotation=true;
                    else if (event.key.code==Keyboard::Left) dx=-1;
                    else if (event.key.code==Keyboard::Right) dx=1;
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)) delay=0.04;
            else delay=0.3;

            rotate_block(rotation, color);

            move_block_horizontally(dx);

            if(is_overlap()){
                withdraw_previous_move(copy);
            }

            draw_field(window);

            draw_block(window);

            window.display();
        }

    attach_fallen_block(color);

    clear_filled_rows();
}

return 0;
}


void initialize_draw_variables(){
    texture_of_tiles.loadFromFile("tiles.png");
    sprite_of_block.setTexture(texture_of_tiles);

    texture_of_field.loadFromFile("grid.png");
    sprite_of_field.setTexture(texture_of_field);

    font.loadFromFile("arial.ttf");
    line1.setFont(font);    line1.setCharacterSize(24);
    line1.setFillColor(Color::Green);    line1.setStyle(Text::Bold);
    line3=line2=line1;
}

void draw_openingwindow(RenderWindow& window){

    line1.setPosition(45, 120);   line2.setPosition(125, 160);   line3.setPosition(80, 200);

    for(int seconds=3; seconds>=0; seconds--){
        line1.setString("Game starts in");
        line2.setString(to_string(seconds));
        line3.setString("seconds!");

        window.draw(line1);   window.draw(line2);   window.draw(line3);

        window.display();
        sleep(milliseconds(900));
        window.clear();
    }
}

bool is_bottom_reached(){
    for(int i=0; i<4; i++){
        if(block[i].y==height-1 || field[block[i].y+1][block[i].x]!=0) return true;
        }
    return false;
}

bool is_overlap(){
    for(int i=1; i<4; i++){
        if(field[block[i].y][block[i].x]!=0) return true;
    }
    for(int i=0; i<4; i++){
        if(block[i].x==-1 || block[i].x==width){
            return true;
        }
    }
return false;
}

void initialize_field(){
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            field[i][j]=0;
        }
    }
}

void set_new_block(const int color){
    for(int i=0; i<4; i++){
        block[i].x=shapes_x[color-1][i]+(width/2)-1;
        block[i].y=shapes_y[color-1][i];
    }
    sprite_of_block.setTextureRect(IntRect(color*pixel, 0, pixel, pixel));
}

bool is_gameover(){
    for(int i=0; i<4; i++){
        if(field[block[i].y][block[i].x]!=0){
            return true;
        }
    }
    return false;
}

void draw_gameoverwindow(RenderWindow& window){

    sleep(milliseconds(1000));
    window.clear();

    line1.setString("Game over!");    line2.setString("Score: " + to_string(score));

    line1.setPosition(60, 120);    line2.setPosition(75, 160);

    window.draw(line1);    window.draw(line2);

    window.display();
    sleep(milliseconds(2000));
    window.close();
}

void stepping_block_downward(){
    for(int i=0; i<4; i++){
        block[i].y=block[i].y+1;
    }
}

void make_blockcopy(Block* copy){
    for(int i=0; i<4; i++){
        copy[i]=block[i];
    }
}

void rotate_block(bool& rotation, const int color){
    if(rotation==true && color!=2){
        for(int i=1; i<4; i++){
        int x=block[i].y-block[0].y;
        int y=block[i].x-block[0].x;
        block[i].x=block[0].x-x;
        block[i].y=block[0].y+y;
        }
        rotation=false;
    }
}

void move_block_horizontally(int& dx){
    for(int i=0; i<4; i++){
        block[i].x=block[i].x+dx;
    }
    dx=0;
}

void withdraw_previous_move(Block* copy){
    for(int i=0; i<4; i++){
        block[i]=copy[i];
    }
}

void draw_field(RenderWindow& window){
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            if(field[i][j]==0){
                sprite_of_field.setPosition(j*pixel, i*pixel);
                window.draw(sprite_of_field);
            }
            else{
                sprite_of_fallenblocks.setTexture(texture_of_tiles);
                sprite_of_fallenblocks.setTextureRect(IntRect(field[i][j]*pixel, 0, pixel, pixel));
                sprite_of_fallenblocks.setPosition(j*pixel, i*pixel);
                window.draw(sprite_of_fallenblocks);
            }
        }
    }
}

void draw_block(RenderWindow& window){
    for(int i=0; i<4; i++){
        sprite_of_block.setPosition(block[i].x*pixel, block[i].y*pixel);
        window.draw(sprite_of_block);
    }
}

void attach_fallen_block(const int color){
    for(int i=0; i<4; i++){
        field[block[i].y][block[i].x]=color;
    }
}

void clear_filled_rows(){
    for(int i=height-1; i>0; i--){
        int counter=0;
        for(int j=0; j<width; j++){
            if(field[i][j]!=0) counter++;
        }
        if(counter==width){
            for(int k=i; k>0; k--){
                for(int j=0; j<width; j++){
                    field[k][j]=field[k-1][j];
                }
            }
            score=score+10;
            i++;
        }
    }
}
