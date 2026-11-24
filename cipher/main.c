#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <unistd.h>

int rc = 0;

void to_uppercase();
void randomize_case();
void caesar_cipher(int key);


int 
main(int argc, char ** argv){
    int rc = 0;
    char opt = 0;
    char *valid_opts = "crk:";
    int randomize = 0;
    int to_caps = 0;
    int cipher = 0;
    int key = 0;
    srandom(time(NULL));


    while ((opt = getopt(argc,argv,valid_opts)) != -1){

        if( opt == '?' ){
            exit(EXIT_FAILURE);
        }
        switch (opt){
            case 'c':
                to_caps = 1;
                break;
            case 'r':
                randomize = 1;
                break;
            case 'k':
                cipher = 1;
                key = atoi(optarg);
                break;
        }
    }
    printf("%d\n",key);
    if(to_caps){
        to_uppercase();
    }
    if(randomize){
        randomize_case();
    }
    if(cipher){
        caesar_cipher(key);
    }


    return EXIT_SUCCESS;
}

void
to_uppercase(){
    int c;
    int caps_diff = abs('a' - 'A');
    while((c = fgetc(stdin)) != EOF){
        if (c > 'a' && c < 'z'){
            c = c -caps_diff;
        }
        rc = fputc(c,stdout);
        fflush(stdout);
        if( rc  == EOF){
            break;
        }
    }
    printf("\n");
}

void
randomize_case(){
    int c;
    int caps_diff = abs('a' - 'A');
    while((c = fgetc(stdin)) != EOF){

        if (c >= 'a' && c <= 'z'){
            if( random()%2 ==0 ){
                c = c - caps_diff;
            }
        } else if (c >= 'A' && c <= 'Z' ){
            if( random()%2 ==0 ){
                c = c + caps_diff;
            }
        }
        rc = fputc(c,stdout);
        fflush(stdout);
        if( rc  == EOF){
            break;
        }
    }
    printf("\n");
}
void
caesar_cipher(int key){
    int c;
    int caps_diff = abs('a' - 'A');
    while((c = fgetc(stdin)) != EOF){

        if ((c > 'a' && c < 'z') ||(c > 'A' && c < 'Z' )){
            if( random()%2 ==0 ){
                c = c - caps_diff;
            }
        }
        rc = fputc(c,stdout);
        fflush(stdout);
        if( rc  == EOF){
            break;
        }
    }
    printf("\n");
}

