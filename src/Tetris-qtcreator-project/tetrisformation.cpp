#include "tetrisformation.hpp"
#include <GL/gl.h>

void TetrisFormation::addPoint(int x, int y)
{
    TetrisPoint new_point;
    new_point.x = x;
    new_point.y = y;
    my_points.push_front(new_point);
}

TetrisFormation::TetrisFormation(TetrisMatrix *matrix, int x, int y)
{
    myMatrix = matrix;
    graph_x = x;
    graph_y = y;
}

void TetrisFormation::setColor(float red, float green, float blue)
{
    my_red = red;
    my_green = green;
    my_blue = blue;
}

void TetrisFormation::render()
{
    for(list<TetrisPoint>::iterator point = my_points.begin(); point != my_points.end(); point++ )
    {
        glPushMatrix();
        glTranslatef(myMatrix->getGraphX() + (graph_x + point->x) * myMatrix->getBlockWidth(),
                     myMatrix->getGraphY() + (graph_y + point->y) * myMatrix->getBlockHeight(), 0);
        TetrisMatrix::renderSquare(myMatrix->getBlockWidth(), myMatrix->getBlockHeight(), my_red, my_green, my_blue);
        glPopMatrix();
    }
}

bool TetrisFormation::canMoveDown()
{
    for(list<TetrisPoint>::iterator point = my_points.begin(); point != my_points.end(); point++ )
    {
        if(!myMatrix->canAddBlock(graph_x + point->x, graph_y + point->y + 1)) return false; //can't move
    }
    return true; //can move
}

bool TetrisFormation::moveDown()
{
    if(canMoveDown())
    {
        graph_y += 1;
        return true; //moved
    }
    return false; //not moved
}

bool TetrisFormation::canMoveLeft()
{
    for(list<TetrisPoint>::iterator point = my_points.begin(); point != my_points.end(); point++ )
    {
        if(!myMatrix->canAddBlock(graph_x + point->x - 1, graph_y + point->y)) return false; //can't move
    }
    return true; //can move
}

bool TetrisFormation::moveLeft()
{
    if(canMoveLeft())
    {
        graph_x -= 1;
        return true; //moved
    }
    else return false; //not moved
}

bool TetrisFormation::canMoveRight()
{
    for(list<TetrisPoint>::iterator point = my_points.begin(); point != my_points.end(); point++ )
    {
        if(!myMatrix->canAddBlock(graph_x + point->x + 1, graph_y + point->y)) return false; //can't move
    }
    return true; //can move
}

bool TetrisFormation::moveRight()
{
    if(canMoveRight())
    {
        graph_x += 1;
        return true; //moved
    }
    else return false; //not moved
}

bool TetrisFormation::clockwiseRotate()
{
    for(list<TetrisPoint>::iterator point = my_points.begin(); point != my_points.end(); point++ )
    {
        if (!myMatrix->canAddBlock(graph_x - point->y, graph_y + point->x)) return false; //cannot rotate
    }

    for(list<TetrisPoint>::iterator point = my_points.begin(); point != my_points.end(); point++ )
    {
        int x = point->x;
        int y = point->y;
        point->x = -y;
        point->y = x;
    }

    return true; //rotated
}

bool TetrisFormation::anticlockwiseRotate()
{
    for(list<TetrisPoint>::iterator point = my_points.begin(); point != my_points.end(); point++ )
    {
        if (!myMatrix->canAddBlock(graph_x + -point->y, graph_y - point->x)) return false; //cannot rotate
    }

    for(list<TetrisPoint>::iterator point = my_points.begin(); point != my_points.end(); point++ )
    {
        int x = point->x;
        int y = point->y;
        point->x = y;
        point->y = -x;
     }

    return true; //rotated
}

bool TetrisFormation::invertX()
{
    for(list<TetrisPoint>::iterator point = my_points.begin(); point != my_points.end(); point++ )
    {
        if (!myMatrix->canAddBlock(graph_x + point->y, graph_y - point->x)) return false; //cannot invert
    }

    for(list<TetrisPoint>::iterator point = my_points.begin(); point != my_points.end(); point++ )
    {
        int x = point->x;
        int y = point->y;
        point->x = -x;
        point->y = y;
     }

    return true; //inverted
}

bool TetrisFormation::invertY()
{
    for(list<TetrisPoint>::iterator point = my_points.begin(); point != my_points.end(); point++ )
    {
        if (!myMatrix->canAddBlock(graph_x - point->y, graph_y + point->x)) return false; //cannot invert
    }

    for(list<TetrisPoint>::iterator point = my_points.begin(); point != my_points.end(); point++ )
    {
        int x = point->x;
        int y = point->y;
        point->x = x;
        point->y = -y;
     }

    return true; //inverted
}

void TetrisFormation::drop()
{
    for(list<TetrisPoint>::iterator point = my_points.begin(); point != my_points.end(); point++ )
    {
        myMatrix->addBlock(graph_x + point->x, graph_y + point->y, my_red, my_green, my_blue);
    }
}
