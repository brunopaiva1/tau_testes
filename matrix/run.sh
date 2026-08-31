#!/bin/bash

rm -f profile.* tautrace.*.trc events.*.edf tau.trc tau.edf traco_final.json
export TAU_MAKEFILE=/home/brunopaiva/tau-2.35.1/x86_64/lib/Makefile.tau-papi-ompt-mpi-openmp
export TAU_TRACE=1
export TAU_OPTIONS="-optOpari -optCompInst -optVerbose"

tau_cxx.sh -fopenmp matrix.cpp -o teste

if [ ! -f ./teste_fases_TAU ]; then
    echo "[Erro] Falha na compilação."
    exit 1
fi

export TAU_TRACE=1

pascalanalyzer ./teste -t tau --taub -c 1,2,4 -i "512" -o resultado.tar