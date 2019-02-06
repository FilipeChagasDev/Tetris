#ifndef TETRISGENERATORS_HPP
#define TETRISGENERATORS_HPP

#include "tetrismatrix.hpp"
#include "tetrisformation.hpp"
#include "formations/tformation.hpp"
#include "formations/lformation.hpp"
#include "formations/oformation.hpp"
#include "formations/_formation.hpp"
#include "formations/sformation.hpp"

TetrisFormation *generateFormation(TetrisMatrix* matrix, int x, int y);
TetrisFormation *getNextFormation();

#endif // TETRISGENERATORS_HPP
