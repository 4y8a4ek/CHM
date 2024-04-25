#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <vector>

class Matrix {
private:
    std::vector<std::vector<double>> data;
    size_t rows;
    size_t cols;

public:
    Matrix();
    Matrix(size_t rows, size_t cols);
    void setElement(size_t row, size_t col,  double value);
    double getElement(size_t row, size_t col) ;
    Matrix operator+(const Matrix& other) ;
    Matrix operator-(const Matrix& other) ;
    Matrix operator*(const Matrix& other) ;
    void print() ;
    Matrix transpose();
    Matrix inverse();
};

#endif