#!/bin/bash

export TAU_MAKEFILE=/home/brunopaiva/tau-2.35.1/x86_64/lib/Makefile.tau-openmp-opari

# export TAU_CXX=g++
# export TAU_CC=gcc

# export TAU_OPTIONS="-optCompInst -optVerbose -optOpari"
export TAU_TRACE=1

rm -f tautrace* events* profile* tau.trc tau.edf teste_tau1 tau_teste.tar *.o *.opari.inc

tau_cxx.sh -optOpari -fopenmp -O2 matrix.cpp -o teste_tau2

# tau_cxx.sh -g -O0 -no-pie -fopenmp matrix_manual.cpp -o teste_tau1

/home/brunopaiva/pascalsuite-analyzer/venv/bin/pascalanalyzer ./teste_tau2 -t tau --taub -r 5 -c 1,2,4,8 -i "2048" -o tau_teste.tar