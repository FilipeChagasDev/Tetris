#ifndef LFORMATION_HPP
#define LFORMATION_HPP
#include "tetrisformation.hpp"
#include "tetrismatrix.hpp"

class LFormation : public TetrisFormation
{
public:
    LFormation(TetrisMatrix *matrix, int x, int y);
};

#endif // LFORMATION_HPP
