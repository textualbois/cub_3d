#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MLX42/MLX42.h"
#include "libft/libft.h"

// default window size
#define WIDTH 800
#define HEIGHT 800

typedef struct s_IntPair{
	int x;
	int y;
}	t_IntPair;

typedef struct s_DoublePair{
	double x;
	double y;
}	t_DoublePair;

typedef struct s_Character{
	t_IntPair size;
	t_IntPair pos;
	float angle;
	mlx_image_t *image;
}	t_character;

typedef struct s_World_Controller{
	mlx_t *window;
	t_character *player;
	mlx_image_t *background;
}	t_World_Controller;

// inits //



t_World_Controller *init_world(void);
mlx_t *initialize_window(void);


t_character* init_mini_charachter(mlx_t *window, t_IntPair size, t_IntPair pos);

void	init_loops_n_hooks(t_World_Controller *world);


//hooks//
void ft_move_pc(void *param);


#endif