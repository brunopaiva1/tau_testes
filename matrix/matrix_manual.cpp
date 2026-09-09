#include <omp.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <TAU.h>


void initialize_matrices(std::vector<double>& A, std::vector<double>& B, int N) {
#pragma omp parallel
    {
        TAU_PROFILE_TIMER(t, "initialize_matrices_loop", " ", TAU_USER);
        TAU_PROFILE_START(t);
#pragma omp for
        for (int i = 0; i < N * N; i++) {
            unsigned int seed = 123 + i;
            A[i] = (double)rand_r(&seed) / RAND_MAX;
            B[i] = (double)rand_r(&seed) / RAND_MAX;
        }
        TAU_PROFILE_STOP(t);
    }
}

void matrix_multiply(const std::vector<double>& A, const std::vector<double>& B, std::vector<double>& C, int N) {
#pragma omp parallel
    {
        TAU_PROFILE_TIMER(t, "matrix_multiply_loop", " ", TAU_USER);
        TAU_PROFILE_START(t);
#pragma omp for
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                double sum = 0.0;
                for (int k = 0; k < N; k++) {
                    sum += A[i * N + k] * B[k * N + j];
                }
                C[i * N + j] = sum;
            }
        }
        TAU_PROFILE_STOP(t);
    }
}

void matrix_add_heavy(const std::vector<double>& C, const std::vector<double>& A, std::vector<double>& D, int N) {
#pragma omp parallel
    {
        TAU_PROFILE_TIMER(t, "matrix_add_heavy_loop", " ", TAU_USER);
        TAU_PROFILE_START(t);
#pragma omp for
        for (int i = 0; i < N * N; i++) {
            double temp = C[i] + A[i];

            for (int k = 0; k < 500; k++) {
                temp += (temp * 0.0001);
            }
            D[i] = temp;
        }
        TAU_PROFILE_STOP(t);
    }
}

int main(int argc, char* argv[]) {
    int N = 512;
    if (argc > 1) {
        N = std::stoi(argv[1]);
    }

    std::vector<double> A(N * N);
    std::vector<double> B(N * N);
    std::vector<double> C(N * N, 0.0);
    std::vector<double> D(N * N, 0.0);

    initialize_matrices(A, B, N);
    matrix_multiply(A, B, C, N);
    matrix_add_heavy(C, A, D, N);

    return 0;
}