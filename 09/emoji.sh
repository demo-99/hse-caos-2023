gcc -m32 -c прикол.c -o прикол.o
objcopy --redefine-sym print_int='😂' прикол.o c_function_emoji.o
as --32 call.S -o call.o
gcc -m32 c_function_emoji.o call.o -o program
./program
