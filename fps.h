#ifndef FPS_H
# define FPS_H

#include <stdio.h>
#include "MLX42/MLX42.h"
#include "libft/libft.h"
#include <math.h>
#include <stdlib.h>

#define INTERVALS 10

typedef struct {
	int frameCounts[INTERVALS];
	int intervalIndex;
	double lastUpdateTime;
}	FrameCounter;

int		init_frame_counter();
void	destroy_frame_counter();
void	update_frame_counter();
double	get_frame_count();

#endif