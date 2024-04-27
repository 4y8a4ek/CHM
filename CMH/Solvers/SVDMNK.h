#ifndef SVDMNK_H
#define SVDMNK_H

#include "../Classes/ClassMatrix.h"
Matrix pseudoInverse( Matrix A);
Matrix solveSystemWithPseudoInverse(Matrix A,  Matrix b);

#endif