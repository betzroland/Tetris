#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

using namespace std;
using namespace sf;

class Block{
    public:
        int x, y;
};

class Engine{
public:
    int M, N;
    int db;
    int y_min;
    bool rotator;
    int color[250];  // Stores the colors of the created blocks.
    Block block[4];
    Block arrived[1000];

    Engine();

    void set_blockshape();  // Setting block shape, and places it into its starting position.

    bool touch_bottom();    // Detects whether a block has touched the bottom of the Tetris-field or not.

    bool touch_block_y();  // Detects whether an arriving block has reached a placed block or not.

    bool touch_block_fromleft(); // Detects whether a block has touched a placed block from left side or not.

    bool touch_block_fromright();  // Detects whether a block has touched a placed block from right side or not.

    bool touch_wallfromleft();      // Detects whether a block has touched the wall from left side or not.

    bool touch_wallfromright();     // Detects whether a block has touched the wall from right side or not.

    bool is_gameover();     //Returns true, if the blocks reached the top of the wall.

    void rotation();    // Function for rotating a block.

    void attach_block();    //Attaches newly arriving block to the array of the fallen ones.

};


#endif // ENGINE_H_INCLUDED
