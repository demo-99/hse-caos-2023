gcc -o factorial factorial.c -fprofile-arcs -ftest-coverage
./factorial
gcov factorial.c
cat factorial.c.gcov
