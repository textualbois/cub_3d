#include "cub3d.h"

void ft_move_pc(void* param)
{
	t_World_Controller *world;
	mlx_t *mlx;
	t_character *player;

	world = (t_World_Controller *)param;
	mlx = world->window;
	player = world->player;

	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		player->image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		player->image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player->image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player->image->instances[0].x += 5;
}