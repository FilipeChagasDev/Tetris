#ifndef TETRISMATRIX_HPP
#define TETRISMATRIX_HPP
#include "tetrisblock.hpp"

class TetrisMatrix
{
private:
    float graph_x, graph_y, graph_width, graph_height;
    float block_width, block_height;
    int tetris_score;
public:
    static const int width = 13;
    static const int height = 26;

    TetrisBlock blocks[width][height];

    TetrisMatrix();

    void clear();
    bool canAddBlock(int x, int y);
    bool canRemoveBlock(int x, int y);
    bool addBlock(int x, int y, float red, float green, float blue);
    bool removeBlock(int x, int y);

    void defineRenderArea(float x, float y, float width, float height );
    static void renderSquare(float width, float height, float red, float green, float blue );
    void render();

    //Getters
    float getGraphX();
    float getGraphY();
    float getGraphWidth();
    float getGraphHeight();
    float getBlockWidth();
    float getBlockHeight();

    //line management by Gustavo Ale
    bool isrowEmpty(int nrow);
    bool isrowFull(int nrow);

    void promptfullRows();

    void removeRow(int nrow);
    void dropRow(int nrow);


    int getTetrisScore() const;
};

#endif // TETRISMATRIX_HPP
