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


//valgrind says there are no mem leaks even with -r -f t.txt but there is some garbled output. check bounds on my printfs
int
tl_snsplitl(const char *src, char ***dest, const size_t n){

  int s = 0; 
  int l_d = 0;

  if(*dest == NULL){
      (*dest) = (char **)malloc(sizeof(char**));
  }

  while(1){
    const char *end_of_word = strchr(src+s, ' ');

    if(end_of_word == NULL){
      end_of_word = strchr(src+s,'\n');
      if(end_of_word == NULL){
        end_of_word = strchr(src+s, '\0');
        if(end_of_word == NULL){
          break;
        }
      }
    }
    size_t dist = end_of_word - (src+s);
    if(src+dist > src+n){
      return -1;
    }
    if(dist == 0){
      break;
    }
    char *w = (char *)malloc((1+dist)*sizeof(char));
    strncpy(w, src+s, dist);
    w[dist] = '\0';
    (*dest) = (char **)realloc((*dest), sizeof(char *)*(l_d+1));
    (*dest)[l_d] = w;
    l_d++;
    s+=dist+1;
  }
  return l_d;
}

char **
tl_sntolower(char ** dest, const char * w, const size_t n){
  if(*dest == NULL){
    (*dest) = (char *)malloc(sizeof(char *));
  }
  (*dest) = strncpy((*dest), w, n);
  for(size_t i = 0; i < n; i++){
    (*dest)[i] = (char)tolower((*dest)[i]);
  }
  return dest;
}

int
r_nato_fgets(FILE * in){
  char *line = NULL;
  size_t MAX_LINE = 256;
  size_t n = 0; 
  while ((n = getline(&line, &MAX_LINE, in)) != -1){
    if (n == 1 && line[0] == '\n'){
      break;
    }
    int s = 0;
    char **items = NULL;
    int l_items = tl_snsplitl(line, &items, n);
    if (l_items == -1){
      perror("separate_by_spaces");
      free(line);
      free(items); // < may leak memory by not freeing each item 
      return -1;
    }

    int i = 0;
    while(i < l_items){
      char * item_lower = NULL;
      tl_sntolower(&item_lower, items[i], strlen(items[i]));
      for(int j = 0; j < sizeof(nato)/sizeof(char *); j++){
        char * nato_lower = NULL;
        tl_sntolower(&nato_lower, nato[j], strlen(nato[j]));
        if (strcmp(nato_lower,item_lower) == 0){
          fprintf(stdout,"%c",nato[j][0]);
        }
        free(nato_lower);
      }

      free(item_lower);
      free((char *)items[i]);
      i++;
    }
    fprintf(stdout,"\n");
    free(items);
    line = NULL;
  }
  if(line != NULL){free(line);}

  return 0;
}

int
nato_fgets(FILE * in){
  
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
    if(argv[i][0] == '-'){
      for(int j = 1; j < strlen(argv[i]); j++){
        switch (argv[i][j]){
          case 's' :
            f_in = stdin; break;
          case 'r' :
            reverse = 1; break;
          case 'f' :
             f_in = fopen(argv[++i],"r"); 
             if(f_in == NULL){
              perror("fopen\n");
              return EXIT_FAILURE;
             }
             break;
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
