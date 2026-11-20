#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static  const char *nato[] = {
"Alfa", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot",
 "Golf", "Hotel", "India", "Juliett", "Kilo", "Lima",
"Mike", "November", "Oscar", "Papa", "Quebec", "Romeo",
"Sierra", "Tango", "Uniform", "Victor", "Whiskey",
"Xray", "Yankee", "Zulu"
};

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
  FILE * f_in = stdin;
  if(strcmp("-f",argv[1]) == 0){
   f_in = fopen(argv[2],"r"); 
   if(f_in == NULL){
    perror("fopen\n");
    return EXIT_FAILURE;
   }
  }else if(strcmp("-s", argv[1]) == 0){
  }
 rc = nato_fgets(f_in); 
 if(f_in != stdin){
   fclose(f_in);
 }


 if(rc == -1) {
  perror("nato_fgets");
  return EXIT_FAILURE;
 }
  return EXIT_SUCCESS;
}
