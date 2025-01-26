#ifndef TYPES_NUMERIC_H
# define TYPES_NUMERIC_H

#include <math.h>
#include <stdlib.h>

// default window size
#define WIDTH 800
#define HEIGHT 800
#define PI 3.14159265

typedef struct s_IntPair{
	int32_t x;
	int32_t y;
}	t_IntPair;

typedef struct s_IntPtrPair{
	int32_t *x;
	int32_t *y;
}	t_IntPtrPair;

typedef struct s_DoublePair{
	double x;
	double y;
}	t_DoublePair;

#endif