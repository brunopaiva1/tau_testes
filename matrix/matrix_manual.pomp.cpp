#include "matrix_manual.cpp.opari.inc"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <TAU.h>


void initialize_matrices(std::vector<double>& A, std::vector<double>& B, int N) {
{
  int pomp2_num_threads = omp_get_max_threads();
  int pomp2_if = 1;
  POMP2_Task_handle pomp2_old_task;
  POMP2_Parallel_fork(&opari2_region_1, pomp2_if, pomp2_num_threads, &pomp2_old_task, opari2_ctc_1 );
#pragma omp parallel POMP2_DLIST_00001 firstprivate(pomp2_old_task) num_threads(pomp2_num_threads)
{   POMP2_Parallel_begin( &opari2_region_1 );
    {
        TAU_PROFILE_TIMER(t, "initialize_matrices_loop", " ", TAU_USER);
        TAU_PROFILE_START(t);
{   POMP2_For_enter( &opari2_region_2, opari2_ctc_2  );
#pragma omp for nowait
        for (int i = 0; i < N * N; i++) {
            unsigned int seed = 123 + i;
            A[i] = (double)rand_r(&seed) / RAND_MAX;
            B[i] = (double)rand_r(&seed) / RAND_MAX;
        }
{ POMP2_Task_handle pomp2_old_task;
  POMP2_Implicit_barrier_enter( &opari2_region_2, &pomp2_old_task );
#pragma omp barrier
  POMP2_Implicit_barrier_exit( &opari2_region_2, pomp2_old_task ); }
  POMP2_For_exit( &opari2_region_2 );
 }
        TAU_PROFILE_STOP(t);
    }
{ POMP2_Task_handle pomp2_old_task;
  POMP2_Implicit_barrier_enter( &opari2_region_1, &pomp2_old_task );
#pragma omp barrier
  POMP2_Implicit_barrier_exit( &opari2_region_1, pomp2_old_task ); }
  POMP2_Parallel_end( &opari2_region_1 ); }
  POMP2_Parallel_join( &opari2_region_1, pomp2_old_task ); }
}

void matrix_multiply(const std::vector<double>& A, const std::vector<double>& B, std::vector<double>& C, int N) {
{
  int pomp2_num_threads = omp_get_max_threads();
  int pomp2_if = 1;
  POMP2_Task_handle pomp2_old_task;
  POMP2_Parallel_fork(&opari2_region_3, pomp2_if, pomp2_num_threads, &pomp2_old_task, opari2_ctc_3 );
#pragma omp parallel POMP2_DLIST_00003 firstprivate(pomp2_old_task) num_threads(pomp2_num_threads)
{   POMP2_Parallel_begin( &opari2_region_3 );
    {
        TAU_PROFILE_TIMER(t, "matrix_multiply_loop", " ", TAU_USER);
        TAU_PROFILE_START(t);
{   POMP2_For_enter( &opari2_region_4, opari2_ctc_4  );
#pragma omp for nowait
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                double sum = 0.0;
                for (int k = 0; k < N; k++) {
                    sum += A[i * N + k] * B[k * N + j];
                }
                C[i * N + j] = sum;
            }
        }
{ POMP2_Task_handle pomp2_old_task;
  POMP2_Implicit_barrier_enter( &opari2_region_4, &pomp2_old_task );
#pragma omp barrier
  POMP2_Implicit_barrier_exit( &opari2_region_4, pomp2_old_task ); }
  POMP2_For_exit( &opari2_region_4 );
 }
        TAU_PROFILE_STOP(t);
    }
{ POMP2_Task_handle pomp2_old_task;
  POMP2_Implicit_barrier_enter( &opari2_region_3, &pomp2_old_task );
#pragma omp barrier
  POMP2_Implicit_barrier_exit( &opari2_region_3, pomp2_old_task ); }
  POMP2_Parallel_end( &opari2_region_3 ); }
  POMP2_Parallel_join( &opari2_region_3, pomp2_old_task ); }
}

void matrix_add_heavy(const std::vector<double>& C, const std::vector<double>& A, std::vector<double>& D, int N) {
{
  int pomp2_num_threads = omp_get_max_threads();
  int pomp2_if = 1;
  POMP2_Task_handle pomp2_old_task;
  POMP2_Parallel_fork(&opari2_region_5, pomp2_if, pomp2_num_threads, &pomp2_old_task, opari2_ctc_5 );
#pragma omp parallel POMP2_DLIST_00005 firstprivate(pomp2_old_task) num_threads(pomp2_num_threads)
{   POMP2_Parallel_begin( &opari2_region_5 );
    {
        TAU_PROFILE_TIMER(t, "matrix_add_heavy_loop", " ", TAU_USER);
        TAU_PROFILE_START(t);
{   POMP2_For_enter( &opari2_region_6, opari2_ctc_6  );
#pragma omp for nowait
        for (int i = 0; i < N * N; i++) {
            double temp = C[i] + A[i];

            for (int k = 0; k < 500; k++) {
                temp += (temp * 0.0001);
            }
            D[i] = temp;
        }
{ POMP2_Task_handle pomp2_old_task;
  POMP2_Implicit_barrier_enter( &opari2_region_6, &pomp2_old_task );
#pragma omp barrier
  POMP2_Implicit_barrier_exit( &opari2_region_6, pomp2_old_task ); }
  POMP2_For_exit( &opari2_region_6 );
 }
        TAU_PROFILE_STOP(t);
    }
{ POMP2_Task_handle pomp2_old_task;
  POMP2_Implicit_barrier_enter( &opari2_region_5, &pomp2_old_task );
#pragma omp barrier
  POMP2_Implicit_barrier_exit( &opari2_region_5, pomp2_old_task ); }
  POMP2_Parallel_end( &opari2_region_5 ); }
  POMP2_Parallel_join( &opari2_region_5, pomp2_old_task ); }
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
