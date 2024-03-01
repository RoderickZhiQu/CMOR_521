#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;


const int BLOCK_SIZE_Str = 16; 

void add(double* A, double* B, double* result, int n) {
    for (int i = 0; i < n * n; ++i) {
        result[i] = A[i] + B[i];
    }
}

void subtract(double* A, double* B, double* result, int n) {
    for (int i = 0; i < n * n; ++i) {
        result[i] = A[i] - B[i];
    }
}

void standardMatrixMultiplication(double* A, double* B, double* C, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i * n + j] = 0;
            for (int k = 0; k < n; ++k) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}

void strassen(double* A, double* B, double* C, int n) {
    if (n <= BLOCK_SIZE_Str) {
        standardMatrixMultiplication(A, B, C, n);
        return;
    }


    int newSize = n / 2;
    double* a11 = new double[newSize * newSize];
    double* a12 = new double[newSize * newSize];
    double* a21 = new double[newSize * newSize];
    double* a22 = new double[newSize * newSize];
    double* b11 = new double[newSize * newSize];
    double* b12 = new double[newSize * newSize];
    double* b21 = new double[newSize * newSize];
    double* b22 = new double[newSize * newSize];

    double* c11 = new double[newSize * newSize];
    double* c12 = new double[newSize * newSize];
    double* c21 = new double[newSize * newSize];
    double* c22 = new double[newSize * newSize];

    double* p1 = new double[newSize * newSize];
    double* p2 = new double[newSize * newSize];
    double* p3 = new double[newSize * newSize];
    double* p4 = new double[newSize * newSize];
    double* p5 = new double[newSize * newSize];
    double* p6 = new double[newSize * newSize];
    double* p7 = new double[newSize * newSize];

    double* aResult = new double[newSize * newSize];
    double* bResult = new double[newSize * newSize];

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            int idx = i * newSize + j;
            a11[idx] = A[i * n + j];
            a12[idx] = A[i * n + j + newSize];
            a21[idx] = A[(i + newSize) * n + j];
            a22[idx] = A[(i + newSize) * n + j + newSize];

            b11[idx] = B[i * n + j];
            b12[idx] = B[i * n + j + newSize];
            b21[idx] = B[(i + newSize) * n + j];
            b22[idx] = B[(i + newSize) * n + j + newSize];
        }
    }

    add(a11, a22, aResult, newSize); 
    add(b11, b22, bResult, newSize); 
    strassen(aResult, bResult, p1, newSize); 

    add(a21, a22, aResult, newSize); 
    strassen(aResult, b11, p2, newSize); 

    subtract(b12, b22, bResult, newSize);
    strassen(a11, bResult, p3, newSize); 

    subtract(b21, b11, bResult, newSize);
    strassen(a22, bResult, p4, newSize);

    add(a11, a12, aResult, newSize);
    strassen(aResult, b22, p5, newSize);

    subtract(a21, a11, aResult, newSize);
    add(b11, b12, bResult, newSize);
    strassen(aResult, bResult, p6, newSize);

    subtract(a12, a22, aResult, newSize);
    add(b21, b22, bResult, newSize);
    strassen(aResult, bResult, p7, newSize);

    add(p3, p5, c12, newSize);
    add(p2, p4, c21, newSize);

    add(p1, p4, aResult, newSize);
    add(aResult, p7, bResult, newSize);
    subtract(bResult, p5, c11, newSize);

    add(p1, p3, aResult, newSize);
    add(aResult, p6, bResult, newSize);
    subtract(bResult, p2, c22, newSize);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i * n + j] = c11[i * newSize + j];
            C[i * n + j + newSize] = c12[i * newSize + j];
            C[(i + newSize) * n + j] = c21[i * newSize + j];
            C[(i + newSize) * n + j + newSize] = c22[i * newSize + j];
        }
    }

    delete[] a11; delete[] a12; delete[] a21; delete[] a22;
    delete[] b11; delete[] b12; delete[] b21; delete[] b22;
    delete[] c11; delete[] c12; delete[] c21; delete[] c22;
    delete[] p1; delete[] p2; delete[] p3; delete[] p4; delete[] p5; delete[] p6; delete[] p7;
    delete[] aResult; delete[] bResult;
}