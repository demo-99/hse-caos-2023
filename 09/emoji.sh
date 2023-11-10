gcc -m32 -c прикол.c -o прикол.o
objcopy --redefine-sym print_int='😂' прикол.o c_function_emoji.o
as --32 call_c_function.S -o call_c_function.o
gcc -m32 c_function_emoji.o call_c_function.o -o program
./program
