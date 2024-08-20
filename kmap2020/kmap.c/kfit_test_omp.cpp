#include "mex.h"
#include <stdio.h>
#include <omp.h>

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// This file is a test for OpenMP parallelization in a MEX function within the 
// MATLAB environment. It demonstrates the use of OpenMP to run parallel code.
//
// Compilation Instruction:
// mex kfit_test_omp.cpp CXXFLAGS="\$CXXFLAGS -fopenmp" LDFLAGS="\$LDFLAGS -fopenmp" -output kfit_test_omp
//
// This will produce a MEX file named 'kfit_test_omp', which you can call from 
// MATLAB to run the parallelized code.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]) {
    
    int maxth;  // Variable to hold the maximum number of threads available
    
    // Get and print the maximum number of threads available
    maxth = omp_get_max_threads();
    printf("Number of threads: %d\n", maxth);
   
    // Parallel region begins here
    #pragma omp parallel
    {
        int th_id = omp_get_thread_num();  // Get the thread ID for each thread
        printf("Hello World from master thread %d\n", th_id);
       
        // Parallel for loop to demonstrate thread usage
        #pragma omp for
        for (int count = 0; count < 6; count++) {
            th_id = omp_get_thread_num();  // Get the thread ID again within the loop
            printf("Hello World from thread %d, %d\n", th_id, count);
        }
    }
    
    // Final message after parallel region ends
    printf("Finished\n");
}
