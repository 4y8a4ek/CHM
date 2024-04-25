#include "QRDecomposition.h"
#include "../Classes/ClassMatrix.h"
Matrix solveLinearSystemQR(Matrix A, Matrix b, int n) {
    Matrix Q(n, n);
    Matrix R(n, n);

    // Perform QR decomposition
    for (size_t j = 0; j < n; ++j) {
        Matrix v(n, 1);
        for (size_t i = 0; i < n; ++i) {
            v.setElement(i, 0, A.getElement(i, j));
        }
        for (size_t i = 0; i < j; ++i) {
            double R_ij = 0.0;
            for (size_t k = 0; k < n; ++k) {
                R_ij += Q.getElement(k, i) * A.getElement(k, j);
            }
            for (size_t k = 0; k < n; ++k) {
                v.setElement(k, 0, v.getElement(k, 0) - Q.getElement(k, i) * R_ij);
            }
            R.setElement(i, j, R_ij);
        }
        double v_norm_sq = 0.0;
        for (size_t i = 0; i < n; ++i) {
            v_norm_sq += v.getElement(i, 0) * v.getElement(i, 0);
        }
        double v_norm = std::sqrt(v_norm_sq);
        if (v_norm < 1e-8) {
            std::cerr << "Matrix is not full rank!" << std::endl;
            return Matrix();
        }
        for (size_t i = 0; i < n; ++i) {
            Q.setElement(i, j, v.getElement(i, 0) / v_norm);
        }
        R.setElement(j, j, v_norm);
    }

    // Solve system Rx = Q^T * b using back substitution
    Matrix Qt_b = Q.transpose() * b;
    Matrix x(n, 1);
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0.0;
        for (size_t j = i + 1; j < n; ++j) {
            sum += R.getElement(i, j) * x.getElement(j, 0);
        }
        x.setElement(i, 0, (Qt_b.getElement(i, 0) - sum) / R.getElement(i, i));
    }

    return x;
}