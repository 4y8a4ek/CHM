#include "../Classes/ClassMatrix.h"
#include <iostream>
#include <vector>
#include <cmath>
#include "else.h"

double Norma(Matrix a, double n){
    double currsum = 0.0;
    for (int i = 0; i < n; i++){
        currsum += a.getElement(i, 0)*a.getElement(i, 0);
    }
    return sqrt(currsum);
}
double Erorr(Matrix A, Matrix B, int n){
    return Norma((A-B), n)/Norma(B, n);   
}