#include "wave3d.cpp.opari.inc"
#include <iostream>
#include <vector>
#include <cmath>
#include <unistd.h>
#include <string>
#include <cstdlib>

#define IDX(i, j, k) ((size_t)(i) * NY * NZ + (size_t)(j) * NZ + (size_t)(k))

int main(int argc, char* argv[]) {
    int N = 100; 

    if (argc > 1) {
        std::string arg1 = argv[1];
        if (arg1 == "-i" && argc > 2) {
            N = std::atoi(argv[2]);
        } else {
            N = std::atoi(argv[1]);
        }
    }

    int NX = N;
    int NY = N;
    int NZ = N;
    int TIME_STEPS = 500;

    float dx = 10.0f;
    float dt = 0.001f;
    float v = 1500.0f;

    size_t total_size = (size_t)NX * NY * NZ;
    
    std::vector<float> p_prev(total_size, 0.0f);
    std::vector<float> p_curr(total_size, 0.0f);
    std::vector<float> p_next(total_size, 0.0f);

    p_curr[IDX(NX/2, NY/2, NZ/2)] = 1000.0f;

    float coef = (v * v * dt * dt) / (dx * dx);

    std::cout << "Grid: " << NX << "x" << NY << "x" << NZ << "\n";

    for (int t = 0; t < TIME_STEPS; ++t) {
        
{
  int pomp2_num_threads = omp_get_max_threads();
  int pomp2_if = 1;
  POMP2_Task_handle pomp2_old_task;
  POMP2_Parallel_fork(&opari2_region_1, pomp2_if, pomp2_num_threads, &pomp2_old_task, opari2_ctc_1 );
        #pragma omp parallel  POMP2_DLIST_00001 firstprivate(pomp2_old_task) num_threads(pomp2_num_threads)
{   POMP2_Parallel_begin( &opari2_region_1 );
        {
            int tid = omp_get_thread_num();

            if (tid == 3 && t == 50) {
                usleep(50000); 
            }

{   POMP2_For_enter( &opari2_region_2, opari2_ctc_2  );
            #pragma omp for collapse(3) schedule(static) nowait
            for (int i = 1; i < NX - 1; ++i) {
                for (int j = 1; j < NY - 1; ++j) {
                    for (int k = 1; k < NZ - 1; ++k) {
                        
                        float laplacian = 
                            p_curr[IDX(i+1, j, k)] + p_curr[IDX(i-1, j, k)] +
                            p_curr[IDX(i, j+1, k)] + p_curr[IDX(i, j-1, k)] +
                            p_curr[IDX(i, j, k+1)] + p_curr[IDX(i, j, k-1)] -
                            6.0f * p_curr[IDX(i, j, k)];

                        p_next[IDX(i, j, k)] = 2.0f * p_curr[IDX(i, j, k)] - p_prev[IDX(i, j, k)] + coef * laplacian;
                    }
                }
            }
{ POMP2_Task_handle pomp2_old_task;
  POMP2_Implicit_barrier_enter( &opari2_region_2, &pomp2_old_task );
#pragma omp barrier
  POMP2_Implicit_barrier_exit( &opari2_region_2, pomp2_old_task ); }
  POMP2_For_exit( &opari2_region_2 );
 }
        }
{ POMP2_Task_handle pomp2_old_task;
  POMP2_Implicit_barrier_enter( &opari2_region_1, &pomp2_old_task );
#pragma omp barrier
  POMP2_Implicit_barrier_exit( &opari2_region_1, pomp2_old_task ); }
  POMP2_Parallel_end( &opari2_region_1 ); }
  POMP2_Parallel_join( &opari2_region_1, pomp2_old_task ); }

{
  int pomp2_num_threads = omp_get_max_threads();
  int pomp2_if = 1;
  POMP2_Task_handle pomp2_old_task;
  POMP2_Parallel_fork(&opari2_region_3, pomp2_if, pomp2_num_threads, &pomp2_old_task, opari2_ctc_3 );
        #pragma omp parallel                                  POMP2_DLIST_00003 firstprivate(pomp2_old_task) num_threads(pomp2_num_threads)
{   POMP2_Parallel_begin( &opari2_region_3 );
{   POMP2_For_enter( &opari2_region_3, opari2_ctc_3  );
        #pragma omp          for collapse(3) schedule(static)                   nowait
        for (int i = 0; i < NX; ++i) {
            for (int j = 0; j < NY; ++j) {
                for (int k = 0; k < NZ; ++k) {
                    p_prev[IDX(i, j, k)] = p_curr[IDX(i, j, k)];
                    p_curr[IDX(i, j, k)] = p_next[IDX(i, j, k)];
                }
            }
        }
{ POMP2_Task_handle pomp2_old_task;
  POMP2_Implicit_barrier_enter( &opari2_region_3, &pomp2_old_task );
#pragma omp barrier
  POMP2_Implicit_barrier_exit( &opari2_region_3, pomp2_old_task ); }
  POMP2_For_exit( &opari2_region_3 );
 }
  POMP2_Parallel_end( &opari2_region_3 ); }
  POMP2_Parallel_join( &opari2_region_3, pomp2_old_task ); }
    }

    return 0;
}
