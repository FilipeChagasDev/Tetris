#include "oformation.hpp"

OFormation::OFormation(TetrisMatrix *matrix, int x, int y) : TetrisFormation(matrix,x,y)
{
    //default color
    my_red = 0;
    my_green = 1;
    my_blue = 1;

    //points
    addPoint(0,0);
    addPoint(1,0);
    addPoint(0,1);
    addPoint(1,1);
}
