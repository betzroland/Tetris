#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

class Block{
    public:
        int x, y;
};

class Engine{
public:
    int M, N;
    int db;
    int y_min;
    bool rotation;
    int color[250];
    Block block[4];
    Block block_copy[4];
    Block arrived[1000];

    Engine();

    void set_blockshape();

    bool touch_bottom();

    bool is_gameover();

    void rotate_block();

    void move_block(float& delay);
    void attach_block();

    bool is_overlap();

};


#endif // ENGINE_H_INCLUDED
