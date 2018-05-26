#ifndef TFORMATION_HPP
#define TFORMATION_HPP
#include "../tetrisformation.hpp"

class TFormation : public TetrisFormation
{
public:
    TFormation(TetrisMatrix *matrix, int x, int y);
};

#endif // TFORMATION_HPP
