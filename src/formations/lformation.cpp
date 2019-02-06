#include "lformation.hpp"

LFormation::LFormation(TetrisMatrix *matrix, int x, int y) : TetrisFormation(matrix,x,y)
{
    //default color
    my_red = 1;
    my_green = 1;
    my_blue = 0;

    //points
    addPoint(0,-1);
    addPoint(1,-1);
    addPoint(0,0);
    addPoint(0,1);
}
