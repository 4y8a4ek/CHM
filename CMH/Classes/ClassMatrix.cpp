#include <iostream>
#include "../Classes/ClassMatrix.h"
#include <cmath>
#include <vector>

const double eps = 1e-15;

Matrix::Matrix() : rows(0), cols(0) {}

Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
    data.resize(rows, std::vector< double>(cols, 0.0));
}

    void Matrix::setElement(size_t row, size_t col,  double value) {
        if (row < rows && col < cols) {
            if(fabs(value) < eps){
                value = 0;
            }


            data[row][col] = value;
            
        } else {
            std::cerr << "Invalid index!" << std::endl;
        }
    }
    
    double Matrix::getElement(size_t row, size_t col){
        if (row < rows && col < cols) {
            return data[row][col];
        } else {
            std::cerr << "Invalid index!" << std::endl;
            return 0.0; // или можно выбросить исключение
        }
    }

    Matrix Matrix::operator+(const Matrix& other){
        if (rows != other.rows || cols != other.cols) {
            std::cerr << "Matrix dimensions don't match!" << std::endl;
            return Matrix();
        }

        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix Matrix::operator-(const Matrix& other){
        if (rows != other.rows || cols != other.cols) {
            std::cerr << "Matrix dimensions don't match!" << std::endl;
            return Matrix();
        }

        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix Matrix::operator*(const Matrix& other){
        if (cols != other.rows) {
            std::cerr << "Matrix dimensions don't match for multiplication!" << std::endl;
            return Matrix();
        }

        Matrix result(rows, other.cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                for (size_t k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    void Matrix::print(){
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    Matrix Matrix::transpose() {
        Matrix result(cols, rows);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.setElement(j, i, data[i][j]); 
            }
        }
        return result;
    }

    Matrix Matrix::inverse() {
        if (rows != cols) {

            std::cerr << "Matrix is not square!" << std::endl;
            return Matrix(0, 0);
        }

        Matrix extended(rows, 2 * cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                extended.setElement(i, j, data[i][j]);
                if (i == j) {
                    extended.setElement(i, j + cols, 1.0);
                }
            }
        }

        for (size_t i = 0; i < rows; ++i) {

            double pivot = extended.getElement(i, i);
            if (pivot == 0) {
                std::cerr << "Matrix is singular!" << std::endl;
            }
            for (size_t j = 0; j < 2 * cols; ++j) {
                extended.setElement(i, j, extended.getElement(i, j) / pivot);
            }

            for (size_t k = 0; k < rows; ++k) {
                if (k != i) {
                    double factor = extended.getElement(k, i);
                    for (size_t j = 0; j < 2 * cols; ++j) {
                        extended.setElement(k, j, extended.getElement(k, j) - factor * extended.getElement(i, j));
                    }
                }
            }
        }

        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.setElement(i, j, extended.getElement(i, j + cols));
            }
        }

        return result;
    }
