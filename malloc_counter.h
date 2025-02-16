#ifndef MALLOC_COUNTER_H
# define MALLOC_COUNTER_H

#include <stdio.h>

#define MALLOC 0
#define IMAGE 1
#define TEXTURE 2
#define OTHER 3
#define RESULT 4
#define PARSER 5

void malloc_counter(int increment, int type, char* info);

#endif
