#include "_formation.hpp"

_Formation::_Formation(TetrisMatrix *matrix, int x, int y) : TetrisFormation(matrix,x,y)
{
    //default color
    my_red = 1;
    my_green = 0;
    my_blue = 1;

    //points
    addPoint(-1,0);
    addPoint(0,0);
    addPoint(1,0);
    addPoint(2,0);
}
