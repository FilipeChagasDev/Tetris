#include "tetrismatrix.hpp"

// Graphics Libs
#ifdef __APPLE__
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif

#include <iostream>

float TetrisMatrix::getGraphX()
{
    return graph_x;
}

float TetrisMatrix::getGraphY()
{
    return graph_y;
}

float TetrisMatrix::getGraphWidth()
{
    return graph_width;
}

float TetrisMatrix::getGraphHeight()
{
    return graph_height;
}

float TetrisMatrix::getBlockWidth()
{
    return block_width;
}

float TetrisMatrix::getBlockHeight()
{
    return block_height;
}

TetrisMatrix::TetrisMatrix()
{
    for(int x = 0; x < TetrisMatrix::width; x++ )
        for(int y = 0; y < TetrisMatrix::height; y++ )
            blocks[x][y].empty = true;
}

void TetrisMatrix::clear()
{
    for(int x = 0; x < TetrisMatrix::width; x++ )
        for(int y = 0; y < TetrisMatrix::height; y++ )
            blocks[x][y].empty = true;
}

bool TetrisMatrix::canAddBlock(int x, int y)
{
    /*if(x < 0 || y < 0 || x > TetrisMatrix::width || y > TetrisMatrix::height) //error case
    {
        std::cerr << "error : coordinates out of range" << std::endl;
        throw;
    }*/

    if(x < 0 || y < 0 || x >= TetrisMatrix::width || y >= TetrisMatrix::height) return false; //can't add
    else
        if(blocks[x][y].empty) return true; //can add
        else return false; //can't add
}

bool TetrisMatrix::canRemoveBlock(int x, int y)
{
    if(x >= TetrisMatrix::width || y >= TetrisMatrix::height) //error case
    {
        std::cerr << "error : coordinates out of range" << std::endl;
        throw;
    }

    if(!blocks[x][y].empty) return true; //can remove
    else return false; //can't remove
}

bool TetrisMatrix::addBlock(int x, int y, float red, float green, float blue)
{
    if(canAddBlock(x,y))
    {
        blocks[x][y].empty = false;
        blocks[x][y].red = red;
        blocks[x][y].green = green;
        blocks[x][y].blue = blue;
        return true; //added
    }
    else return false; //not added
}

bool TetrisMatrix::removeBlock(int x, int y)
{
    if(canRemoveBlock(x,y))
    {
        blocks[x][y].empty = true;
        return true; //removed
    }
    else return false; //not removed
}

void TetrisMatrix::defineRenderArea(float x, float y, float width, float height)
{
    graph_x = x;
    graph_y = y;
    graph_width = width;
    graph_height = height;
    block_width = width / TetrisMatrix::width;
    block_height = height / TetrisMatrix::height;
}

void TetrisMatrix::renderSquare(float width, float height, float red, float green, float blue)
{
    glBegin(GL_POLYGON); //square
        glColor3f(red, green, blue); //top color
            glVertex2f(1,1); //top left vertex
        glColor3f(red - 0.3f, green - 0.3f, blue - 0.3f); //bottom color
            glVertex2f(1, height -1); //bottom left vertex
            glVertex2f(width - 1, height - 1); //bottom right vertex
        glColor3f(red, green, blue); //top color
            glVertex2f(width - 1, 1); //top right vertex
    glEnd();
}

void TetrisMatrix::render()
{
    float current_red, current_green, current_blue;
    TetrisBlock *current_block;
    for(int x = 0; x < TetrisMatrix::width; x++)
        for(int y = 0; y < TetrisMatrix::height; y++ )
        {
            current_block = &blocks[x][y];
            current_red = current_block->red;
            current_green = current_block->green;
            current_blue = current_block->blue;

            if(!current_block->empty)
            {
                glPushMatrix();
                glTranslatef(graph_x + x*block_width,
                             graph_y + y*block_height, 0); //translate matrix to where this block will be drawn
                renderSquare(block_width, block_height, current_red, current_green, current_blue);
                glPopMatrix();
            }
        }
}

//alterations by Gustavo Ale
bool TetrisMatrix::isrowFull(int nrow)
{

    for(int x = 0; x < TetrisMatrix::width; x++)
    {
        if(blocks[x][nrow].empty)
        {
            return false;
        }
    }
    return true;
}

bool TetrisMatrix::isrowEmpty(int nrow)
{

    for(int x = 0; x < TetrisMatrix::width; x++)
    {
        if(!blocks[x][nrow].empty)
        {
            return false;
        }
    }
    return true;
}

void TetrisMatrix::promptfullRows(void)
{
    int fullrows = 0;
    for(int y = 0 ; y < TetrisMatrix::height; y++ )
    {
        if(isrowFull(y))
        {
               std::cout << "Row: " << y << "is full" << std::endl;
               removeRow(y);
               fullrows++;
        }
    }
    if(fullrows >= 4)
    {
        std::cout << "Tetris!!!" << std::endl;
        //score
    }
}

void TetrisMatrix::dropRow(int nrow)
{
    if(isrowEmpty(nrow+1))
    {
        for(int x = 0; x < TetrisMatrix::width; x++)
        {
            blocks[x][nrow+1].red   =   blocks[x][nrow].red;
            blocks[x][nrow+1].green =   blocks[x][nrow].green;
            blocks[x][nrow+1].blue  =   blocks[x][nrow].blue;
            blocks[x][nrow+1].empty =   blocks[x][nrow].empty;

            blocks[x][nrow].empty = true;
        }
    }

}
void TetrisMatrix::removeRow(int nrow)
{
    for(int x = 0; x < TetrisMatrix::width; x++)
    {
        removeBlock(x,nrow);
    }
    for(int y = nrow - 1; y >= 0; y --)
    {
        dropRow(y);
    }
}


//end of Gustavo Ale alterations
