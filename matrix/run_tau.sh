#!/bin/bash

export TAU_MAKEFILE=/home/brunopaiva/tau-2.35.1/x86_64/lib/Makefile.tau-papi-ompt-mpi-openmp
export TAU_TRACE=1

tau_cxx.sh -fopenmp matrix.cpp -o teste_tau
./teste_tau $1