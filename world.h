#ifndef WORLD_H
# define WORLD_H

#include "cub3d.h"
#include "fps.h"

typedef struct s_World_Controller{
	mlx_t			*window;
	t_character		*player;
	mlx_image_t		*minimap;
	t_FrameCounter	*frameCounter;
}	t_World_Controller;

t_World_Controller *init_world(int map[]);

#endif