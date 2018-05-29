#include "sformation.hpp"

SFormation::SFormation(TetrisMatrix *matrix, int x, int y) : TetrisFormation(matrix,x,y)
{
    //default color
    my_red = 1;
    my_green = 0;
    my_blue = 0;

    //points
    addPoint(-1,0);
    addPoint(0,0);
    addPoint(0,1);
    addPoint(1,1);
}
