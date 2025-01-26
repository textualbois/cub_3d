#ifndef MINI_MAP_H
# define MINI_MAP_H

#include "MLX42/MLX42.h"
#include "types_numeric.h"

// typedef struct s_MiniMap{
// 	mlx_image_t *image;
// 	int width;
// 	int height;
// }	t_MiniMap;

mlx_image_t *init_minimap(mlx_t *window, int map[]);

#endif
