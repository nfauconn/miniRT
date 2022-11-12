#!/usr/bin/env bash

clear
set -e
gcc -o crit_test criterion_test1.c -I/mnt/nfs/homes/rokerjea/sgoinfre/Criterion/include -L/mnt/nfs/homes/rokerjea/sgoinfre/Criterion/build/src -W -Wall -Wextra -Werror -lcriterion

./crit_test

clang -o tuple tuple.c -I/mnt/nfs/homes/rokerjea/sgoinfre/Criterion/include -L/mnt/nfs/homes/rokerjea/sgoinfre/Criterion/build/src -W -Wall -Wextra -Werror -mavx -lm -lcriterion

./tuple