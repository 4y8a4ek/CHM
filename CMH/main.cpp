#include "./Classes/ClassMatrix.h"
#include "./Solvers/LUDecomposition.h"
#include "./Else/else.h"
#include "./Solvers/QRDecomposition.h"
#include <iostream>
#include <chrono>
using namespace std;


int main(){
    const int n = 800;
    Matrix A(n,n);
    for( int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            A.setElement(i, j, 1.0 - 0.1*i + 0.5*j);
        }
        A.setElement(i, i, 100.0);
    }

    Matrix b(n, 1);
    for(int i = 0; i < n ; i++)
        b.setElement(i, 0, 1.0);
    Matrix f = A*b;

//LU DECOMPOSITION

    auto startLU = std::chrono::high_resolution_clock::now();
    Matrix xlu = solveSystemUsingLU(A, n, f);
    auto endLU = std::chrono::high_resolution_clock::now();
    auto est_LU_time = std::chrono::duration_cast<std::chrono::milliseconds>(endLU - startLU).count()/1000.0;
    std::cout << "Time LU taken: " << est_LU_time << " seconds" << std::endl;

    double erorr_LU = Erorr(xlu, b, n);
    cout << "Erorr for LU: " << erorr_LU  << endl;

//QR DECOMPOSITION
    auto startQR = std::chrono::high_resolution_clock::now();
    Matrix xqr = solveLinearSystemQR(A, f, n);
    auto endQR = std::chrono::high_resolution_clock::now();
    auto est_QR_time = std::chrono::duration_cast<std::chrono::milliseconds>(endQR - startQR).count()/1000.0;
    std::cout << "Time QR taken: " << est_QR_time << " seconds" << std::endl;

    double erorr_QR = Erorr(xqr, b, n);
    cout << "Erorr for QR: " << erorr_QR  << endl;

    return 0;
}