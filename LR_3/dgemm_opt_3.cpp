#pragma GCC optimize("O3")
#pragma GCC target ("avx2")
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

void DGEMM_opt_3(double** matrixA, double** matrixB, double** matrixC, int N){
    for (int i = 0; i < N; i++)
        for (int k = 0; k < N; k++)
            for (int j = 0; j < N; j++)
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
}

int main(int argc, char* argv[]){
    srand(time(NULL));

    int N = atoi(argv[1]);
    int blockSize = atoi(argv[2]);

    double** matrixA;
    double** matrixB;
    double** matrixC;

    matrixA = new double* [N * sizeof(double*)];
    matrixB = new double* [N * sizeof(double*)];
    matrixC = new double* [N * sizeof(double*)];

    for (int i = 0; i < N; i++)	{
        matrixA[i] = new double[N * sizeof(double)];
        matrixB[i] = new double[N * sizeof(double)];
        matrixC[i] = new double[N * sizeof(double)];
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)		{
            matrixA[i][j] = static_cast<double>(rand() % 10000);
            matrixB[i][j] = static_cast<double>(rand() % 10000);
            matrixC[i][j] = 0.0;
        }

    double time = (double)clock(), result = 0.0;

    DGEMM_opt_3(matrixA, matrixB, matrixC, N);

    result = (double)((clock() - time) / CLOCKS_PER_SEC);

    ofstream file("results.csv", ios_base::out | ios_base::app);
    file << "DGEMM_opt_3" << "," << to_string(N) << "," << to_string(result) << "\n";
    file.close();

    for (int i = 0; i < N; i++) {
        delete[] matrixA[i];
        matrixA[i] = nullptr;
        delete[] matrixB[i];
        matrixB[i] = nullptr;
        delete[] matrixC[i];
        matrixC[i] = nullptr;
    }
    delete[] matrixA;
    matrixA = nullptr;
    delete[] matrixB;
    matrixA = nullptr;
    delete[] matrixC;
    matrixA = nullptr;

    return 0;
}