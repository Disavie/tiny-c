#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>


#define LONG_OPT_CNT 10

int rc = 0;

void niceify_me();
void to_uppercase();
void to_hex();
void randomize_case();
void caesar_cipher(int key);


int 
main(int argc, char ** argv){
    int rc = 0;
    char opt = 0;
    char *ops = "crk:h";
    int randomize = 0;
    int to_caps = 0;
    int cipher = 0;
    int key = 0;
    int hex = 0;
    int nice = 0;

    struct option long_opts[LONG_OPT_CNT] = {
        {"to-hex",    0, NULL,      'h'},
        {"cipher",    1, NULL,      'k'},
        {"to-caps",   0, NULL,      'c'},
        {"randomize", 0, NULL,      'r'},
        {"niceify",   0, NULL,      'n'},
    };
    srandom(time(NULL));

    while ((opt = getopt_long(argc,argv, ops, long_opts, NULL)) != -1){
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
            case 'h':
                hex = 1;
                break;
            case 'n':
                nice = 1;
                break;
                    
        }
    }
    printf("%d\n",cipher);
    if(to_caps){
        to_uppercase();
    }
    if(randomize){
        randomize_case();
    }
    if(cipher){
        caesar_cipher(key);
    }
    if(hex){
        to_hex();
    }
    if(nice){
        niceify_me();
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
    while((c = fgetc(stdin)) != EOF){
        if (tolower(c) >= 'a' && tolower(c) <= 'z'){
            c -= 'a';
            c = (c + key)%26;
            c += 'a';
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
to_hex(){
    int c;
    while((c = fgetc(stdin)) != EOF){
        if(isalnum(c)){
            fprintf(stdout,"%x",c - '0');
        }else{
            rc = fputc(c,stdout);
        }
        fflush(stdout);
        if( rc  == EOF){
            break;
        }
    }
    printf("\n");
}

void
niceify_me(){
    int c;
    int i = 0;
    char buf[512] = {0};
    char *evilword = "hate";
    char *niceword = "love";
    while((c = fgetc(stdin)) != EOF){
        if(c != '\n')
            buf[i++] = c;
        else{
            char *t;
            while((t = strstr(buf,evilword)) != NULL){
                memcpy(t,niceword, strlen(niceword));
            }
            buf[i] = '\n';
            fprintf(stdout,"%s",buf);
            i = 0;
            memset(buf, 0, sizeof(buf));
        }
    }
    printf("\n");
}
