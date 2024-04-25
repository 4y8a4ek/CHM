#include "../Classes/ClassMatrix.h"
#include "LUDecomposition.h"
#include <vector>
#include <iostream>

std::pair<Matrix, Matrix> LUDecomposition(Matrix A, int n){
    Matrix L(n, n);
    Matrix U(n, n);
    double currsum;
    U = A;
    for(int i = 0; i < n; i++)
		for(int j = i; j < n; j++)
			L.setElement(j, i, U.getElement(j, i)/U.getElement(i, i));
	
	for(int k = 1; k < n; k++)
	{
		for(int i = k-1; i < n; i++)
			for(int j = i; j < n; j++)
				L.setElement(j, i, U.getElement(j, i)/U.getElement(i, i));

		for(int i = k; i < n; i++)
			for(int j = k-1; j < n; j++)
				U.setElement(i, j, U.getElement(i, j) - L.getElement(i, k-1)*U.getElement(k-1, j));
    }
    return std::make_pair(L, U);
}

Matrix solveSystemUsingLU( Matrix A, int n, Matrix f) {
    // Решение системы Ly = f для y
    std::pair<Matrix, Matrix> LU = LUDecomposition(A, n);
    Matrix L = LU.first;
    Matrix U = LU.second;
    Matrix y(n, 1);


    for (int i = 0; i < n; ++i) {
        long double sum = 0.0;
        for (int j = 0; j < i; ++j) {
            sum += L.getElement(i, j) * y.getElement(j, 0);
        }
        y.setElement(i, 0, (f.getElement(i, 0) - sum) / L.getElement(i, i));
    }
    // Решение системы Ux = y для x
    Matrix x(n, 1);
    for (int i = n - 1; i >= 0; --i) {
        long double sum = 0.0;
        for (int j = i + 1; j < n; ++j) {
            sum += U.getElement(i, j) * x.getElement(j, 0);
        }
        x.setElement(i, 0, (y.getElement(i, 0) - sum) / U.getElement(i, i));
    }

    return x;
}
