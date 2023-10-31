#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

void DGEMM_opt_2(double** matrixA, double** matrixB, double** matrixC, int N, int blockSize) {
    for (int jj = 0; jj < N; jj += blockSize)
        for (int kk = 0; kk < N; kk += blockSize)
            for (int i = 0; i < N; i++)
                for (int j = jj; j < ((jj + blockSize) > N ? N : (jj + blockSize)); j++) {
                    double temp = 0.0;
                    for (int k = kk; k < ((kk + blockSize) > N ? N : (kk + blockSize)); k++)
                        temp += matrixA[i][k] * matrixB[k][j];
                    matrixC[i][j] += temp;
                }
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

    DGEMM_opt_2(matrixA, matrixB, matrixC, N, blockSize);

    result = (double)((clock() - time) / CLOCKS_PER_SEC);

    cout << result;
    if (N != 1024 && N != 512){
        ofstream file("results.csv", ios_base::out | ios_base::app);
        file << "DGEMM_opt_2" << "," << to_string(N) << "," << to_string(result) << "\n";
        file.close();
    }

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
