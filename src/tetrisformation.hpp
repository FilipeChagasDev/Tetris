#ifndef TETRISFORMATION_HPP
#define TETRISFORMATION_HPP
#include <list>
#include "tetrismatrix.hpp"
using namespace std;

class TetrisPoint
{
public:
    int x, y;
};

class TetrisFormation
{
protected:
    int graph_x, graph_y;
    float my_red, my_green, my_blue; //Block's color

    TetrisMatrix *myMatrix;
    list<TetrisPoint> my_points; //my pointers
    void addPoint(int x, int y);
public:
    bool allow_everything;

    TetrisFormation(TetrisMatrix *matrix, int x, int y);
    void setColor(float red, float green, float blue);
    void render();
    void renderSample(int x, int y);

    bool canMoveDown();
    bool moveDown();

    bool canMoveLeft();
    bool moveLeft();

    bool canMoveRight();
    bool moveRight();

    bool clockwiseRotate();
    bool anticlockwiseRotate();

    bool invertX();
    bool invertY();

    void drop();
};

#endif // TETRISFORMATION_HPP
