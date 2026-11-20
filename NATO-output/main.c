#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

static  const char *nato[] = {
"Alfa", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot",
 "Golf", "Hotel", "India", "Juliett", "Kilo", "Lima",
"Mike", "November", "Oscar", "Papa", "Quebec", "Romeo",
"Sierra", "Tango", "Uniform", "Victor", "Whiskey",
"Xray", "Yankee", "Zulu"
};


#define MAX_WORD_LEN 512
int tl_separate_by_spaces(const char *src, char **dest){

  
  int s = 0; 
  const char *end_of_word = strchr(src, ' ');
  if(end_of_word == NULL){
    end_of_word = strchr(src,'\n');
    if(end_of_word == NULL){
      end_of_word = strchr(src, '\0');
      if(end_of_word == NULL){
        return -1;
      }
    }
  }
  size_t dist = end_of_word - src+s;
  char word[MAX_WORD_LEN] = {0};
  strncpy(word, src+s, dist);
  word[MAX_WORD_LEN-1] = '\0'; // I love saftey!
  printf("read %ld chars into the string: %s\n", dist, word);

  return dist;
}

int r_nato_fgets(FILE * in){
  char word[MAX_WORD_LEN]; 
  char *line = NULL;
  size_t n = 0; 
  while ((n = getline(&line, &n, in)) != -1){
    if (n == 1 && line[0] == '\n'){
      break;
    }
    int s = 0;
    char *items = NULL;
    tl_separate_by_spaces(line, &items);

    free(line);
    line = NULL;
  }

  free(line);
  return 0;
}

int nato_fgets(FILE * in){
  
  char *line = NULL;
  size_t n = 0; 
  while ((n = getline(&line, &n, in)) != -1){
    if (n == 1 && line[0] == '\n'){
      break;
    }
    for(int i = 0 ; i < n ; i++){
      char line_c = line[i];
      for(int j = 0; j < sizeof(nato)/sizeof(char *); j++){
        if (toupper(line_c) == nato[j][0]){
          fprintf(stdout,"%s ",nato[j]);
        }
      }
    }
    free(line);
    line = NULL;
  }

  free(line);
  return 0;
}


int main(int argc, char * argv[]){

  int rc;
  if(argc <2){
    printf("provide -f [filename] or -s to type into stdin\n");
    return EXIT_SUCCESS;
  }
  FILE * f_in = NULL;
  int reverse = 0; // <reverse indicates nato -> english, default is off
  int i = 1;
  while(i < argc){
  // Check -[opt] [input] options first
    if(strcmp("-f",argv[i]) == 0){
     f_in = fopen(argv[++i],"r"); 
     if(f_in == NULL){
      perror("fopen\n");
      return EXIT_FAILURE;
     }
    }else {
      for(int j = 1; j < strlen(argv[i]); j++){
        switch (argv[i][j]){
          case 's' :
            f_in = stdin; break;
          case 'r' :
            reverse = 1; break;
        }
      }
    }
    i++;
  }

  if(f_in == NULL){
    fprintf(stderr, "dude you gotta specify an input with -s or -t\n");
    return EXIT_FAILURE;
  }

  if(reverse){
     rc = r_nato_fgets(f_in); 
  }else{
    rc = nato_fgets(f_in);
  }
  if(f_in != stdin){
     fclose(f_in);
  }


 if(rc == -1) {
  perror("nato_fgets");
  return EXIT_FAILURE;
 }
  return EXIT_SUCCESS;
}
