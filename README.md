Following the Dan Gookin book for Tiny C projects to refresh my C code and for fun


create lib with 2 steps 
1. gcc tiny_lib.c -o 
2. ar rfs libtiny_lib.a tiny_lib.c
ar {otps} {libname} {target file}
*libname* needs to be in libNAME.a format since thats how gcc expects it
then compiling the program
gcc {...} -L.. -l[NAME]
