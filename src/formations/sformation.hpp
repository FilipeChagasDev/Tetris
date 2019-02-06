#ifndef SFORMATION_HPP
#define SFORMATION_HPP
#include "../tetrisformation.hpp"
#include "../tetrismatrix.hpp"

class SFormation : public TetrisFormation
{
public:
    SFormation(TetrisMatrix *matrix, int x, int y);
};

#endif // SFORMATION_HPP
