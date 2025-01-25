#ifndef CHARACTER_H
# define CHARACTER_H

#include "cub3d.h"

typedef struct s_Character{
	t_IntPair size;
	t_IntPtrPair pos;
	float angle;
	mlx_image_t *image;
}	t_character;

// init
t_character* init_mini_character(mlx_t *window, t_IntPair size, t_IntPair pos);

// free

// move

// draw

void ft_color_mini_character_direction(mlx_image_t *player, int color, float angle);
void ft_color_mini_character(mlx_image_t *player, int color);


#endif