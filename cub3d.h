#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MLX42/MLX42.h"
#include "libft/libft.h"
#include "world.h"

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


// inits //

mlx_t *initialize_window(void);
mlx_image_t *init_minimap(mlx_t *window, int map[]);
void	init_loops_n_hooks(t_World_Controller *world);

//hooks//
void ft_move_pc(void *param);

#endif