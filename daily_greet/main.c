#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "../tiny_lib.h"
#include <string.h>

#define LEN 256
#define MOTD_PATH "/home/davis/projects/tiny-c/daily_greet/motd.txt"

int main(int argc, char ** argv){

  char * msg_end;
  if(argc > 1){
    msg_end = argv[1];
  }else{
    msg_end = "freak";
  }
// extern time_t time (time_t *__timer) __THROW;
   time_t current;
   time(&current);
//   fprintf(stdout,"The current time is: %s\n", ctime(&current));
  struct tm *clock = localtime(&current);
  int hr = clock->tm_hour;
  if (hr < 12 && hr > 4){
    fprintf(stdout, "Good morning, %s.\n", msg_end);
  }
  else if (hr > 12 && hr < 22){
    fprintf(stdout, "Good afternoon, %s.\n", msg_end);
  }else{
    fprintf(stdout, "Hey %s, why are you awake right now?\n", msg_end);
  }

  char time_str[LEN];

  strftime(time_str, LEN, "%A, %D %l:%M:%S %P", clock);
  fprintf(stdout, "Current time: %s\n", time_str);
  int phase_d = tl_moon_phase(
    clock->tm_year+1900,
    clock->tm_mon+1,
    clock->tm_mday);
    
  fprintf(stdout, "Moonphase is: %s\n", tl_phase[phase_d]);

  srandom(time(NULL));
  FILE *fd = fopen(MOTD_PATH, "r" );
  if ( fd == NULL ){
    perror("failed to open motd");
  }
  int start = ftell(fd);

  char entry[LEN]; //< One entry should be no longer than LEN
  char *entries[LEN]; //< Expecting no more than LEN entries from the file
  int n = 0;
  while(fgets(entry,LEN,fd) != NULL){
     
     int end = ftell(fd);
     entries[n] = (char *)malloc(end-start * sizeof(char));
     strncpy(entries[n], entry, (ssize_t)end - start);
     n++;

  }
  int the_chosen = rand() % n;
  fprintf(stdout,"%s",entries[the_chosen]); //<Don't need \n since thats copied from the motd.txt
  goto cleanup;

  cleanup:

  for(int i = 0 ; i < n ; i++){
    free(entries[i]);
  }
  fclose(fd);
  return EXIT_SUCCESS;
}

