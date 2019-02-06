#ifndef _FORMATION_HPP
#define _FORMATION_HPP
#include "../tetrisformation.hpp"
#include "../tetrismatrix.hpp"

class _Formation : public TetrisFormation
{
public:
    _Formation(TetrisMatrix *matrix, int x, int y);
};

#endif // _FORMATION_HPP
