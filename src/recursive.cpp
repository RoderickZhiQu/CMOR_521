#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int BLOCK_SIZE = 16; 

void microkernel(int n, double* C, double* A, double* B, int stride) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double sum = 0.0;
            for (int k = 0; k < n; ++k) {
                sum += A[i*stride + k] * B[k*stride + j];
            }
            C[i*stride + j] += sum;
        }
    }
}

void matmul_recursive(int n, double* C, double* A, double* B, int originalStride) {
    if (n <= BLOCK_SIZE) {
        microkernel(n, C, A, B, originalStride);
        return;
    }

    int half = n / 2;
    for (int row = 0; row < n; row += half) {
        for (int col = 0; col < n; col += half) {
            for (int inner = 0; inner < n; inner += half) {
                double* subC = C + row*originalStride + col;
                double* subA = A + row*originalStride + inner;
                double* subB = B + inner*originalStride + col;
                matmul_recursive(half, subC, subA, subB, originalStride);
            }
        }
    }
}