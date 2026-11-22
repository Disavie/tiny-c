#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <unistd.h>

int main(int argc, char ** argv){
    int rc = 0;
    char opt = 0;
    char *valid_opts = "abc:";
    while ((opt = getopt(argc,argv,valid_opts)) != -1){

        if( opt == '?' ){
            exit(EXIT_FAILURE);
        }
        printf("opt: %c\n", opt);
        switch (opt){
            case 'c':
                printf("%s\n",optarg);
                break;
        }
    }
    return EXIT_SUCCESS;
}
