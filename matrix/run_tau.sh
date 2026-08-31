#!/bin/bash

export TAU_MAKEFILE=/home/brunopaiva/tau-2.35.1/x86_64/lib/Makefile.tau-ompt-openmp
export TAU_TRACE=1

rm -f tautrace* events* profile* tau.trc tau.edf teste_tau

tau_cxx.sh -fopenmp matrix.cpp -o teste_tau
./teste_tau $1

tau_multimerge