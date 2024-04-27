#include "../Classes/ClassMatrix.h"

Matrix pseudoInverse(Matrix A) {

    Matrix A_transpose = A.transpose();
    Matrix pseudo_inv_A = (A_transpose * A).inverse() * A_transpose;
    return pseudo_inv_A;
}


Matrix solveSystemWithPseudoInverse(Matrix A,  Matrix b) {
    Matrix pseudo_inv_A = pseudoInverse(A);
    Matrix x = pseudo_inv_A * b;
    return x;
}