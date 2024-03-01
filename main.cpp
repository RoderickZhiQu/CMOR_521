#include <iostream>
#include <chrono>
#include "src/strassen.cpp"
#include "src/recursive.cpp"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <matrix size>" << endl;
        return 1;
    }

    int n = atoi(argv[1]);
    double* A = new double[n * n];
    double* B = new double[n * n];
    double* C = new double[n * n];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i * n + j] = (i == j) ? 1.0 : 0.0;
            B[i * n + j] = (i == j) ? 1.0 : 0.0;
            C[i * n + j] = 0.0;
        }
    }

    auto start_rec = high_resolution_clock::now();
    matmul_recursive(n, C, A, B, n);
    auto end_rec = high_resolution_clock::now();
    auto elapsed_rec = duration_cast<duration<double>>(end_rec - start_rec).count();

    fill_n(C, n*n, 0.0);

    auto start_strassen = high_resolution_clock::now();
    strassen(A, B, C, n);
    auto end_strassen = high_resolution_clock::now();
    auto elapsed_strassen = duration_cast<duration<double>>(end_strassen - start_strassen).count();

    bool correct = true;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if ((i == j && fabs(C[i * n + j] - 1) > 1e-9) || 
                (i != j && fabs(C[i * n + j]) > 1e-9)) {
                correct = false;
                break;
            }
        }
        if (!correct) break;
    }

    cout << "Matrix size: " << n << endl;
    cout << "Recursive Elapsed time: " << elapsed_rec * 1000 << " ms" << endl;
    cout << "Strassen Elapsed time: " << elapsed_strassen * 1000 << " ms" << endl;
    cout << "Correctness check: " << (correct ? "Passed, C is an identity matrix." : "Failed, C is not an identity matrix.") << endl;

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}
