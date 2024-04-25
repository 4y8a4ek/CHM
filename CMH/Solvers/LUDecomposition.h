#ifndef LUDecomposition_H
#define LUDecomposition_H

#include "../Classes/ClassMatrix.h"
#include <iostream>
#include <vector>

std::pair<Matrix, Matrix> LUDecomposition(Matrix A, int n);
Matrix solveSystemUsingLU( Matrix A, int n, Matrix f);

#endif