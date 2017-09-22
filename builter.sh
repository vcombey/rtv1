#!/bin/bash

cd cl; ./makesh.sh rt_cl; cd ..;

find cl -name "*.c" | xargs echo cl/rt_cl.h | xargs cat > built.cl

#cat rt_cl.h *.c opp/*.c > built.cl

