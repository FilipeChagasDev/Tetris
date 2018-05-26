#ifndef OFORMATION_HPP
#define OFORMATION_HPP
#include "tetrisformation.hpp"
#include "tetrismatrix.hpp"

class OFormation : public TetrisFormation
{
public:
    OFormation(TetrisMatrix *matrix, int x, int y);
};

#endif // OFORMATION_HPP
