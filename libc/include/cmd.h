#ifndef _CMD_H
#define _CMD_H 1

#include <stdint.h>

void init_loldle(int rand);
bool loldle(char* guess);
void switchside (void);
void help (void);
void ff (void);
bool surrender_vote(char* l);

#endif
