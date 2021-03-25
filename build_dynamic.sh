# This is what gets called during run time to recompile dynamic.c
echo 'gcc'
gcc -c -fPIC ./src/dynamic.c -o dynamic.o
gcc dynamic.o -shared -o dynamic.so
