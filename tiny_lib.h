#ifndef TINYLIB_H
#define TINYLIB_H
// Returns the moonphase as an int, should be used with tl_phase
int tl_moon_phase(int year,int month,int day);

extern char *tl_phase[8];
#endif
