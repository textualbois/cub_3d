#ifndef WORLD_H
# define WORLD_H

#include "MLX42/MLX42.h"
#include "character.h"
#include "fps.h"
#include "window.h"
#include "mini_map.h"

typedef struct s_World_Controller{
	mlx_t			*window;
	t_character		*player;
	mlx_image_t		*minimap;
	mlx_image_t		*miniCharacter;
	//t_FrameCounter	*frameCounter;
}	t_World_Controller;

t_World_Controller	*init_world(int map[]);

int					init_images(t_World_Controller *world, int map[]);
mlx_image_t			*init_image_mini_character(mlx_t *window, t_character *player, t_IntPair size);
mlx_image_t			*init_image_minimap(mlx_t *window, int map[]);

#endif