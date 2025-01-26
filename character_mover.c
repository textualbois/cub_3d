#include "character.h"

void ft_move_pc(void* param)
{
	t_World_Controller *world;
	mlx_t *mlx;
	t_character *player;

	world = (t_World_Controller *)param;
	mlx = world->window;
	player = world->player;

	if (mlx_is_key_down(mlx, MLX_KEY_Q)) {
		player->angle += 0.1;  // Decrease angle by 1 degree in radians
		if (player->angle < 0) player->angle += 2 * PI;  // Wrap around if the angle goes below 0
	}
	if (mlx_is_key_down(mlx, MLX_KEY_E)) {
		player->angle -= 0.1;  // Increase angle by 1 degree in radians
		if (player->angle >= 2 * PI) player->angle -= 2 * PI;  // Wrap around if the angle exceeds 2π
	}
	// Moving the character in the direction it faces
	if (mlx_is_key_down(mlx, MLX_KEY_W)) {
		*(player->pos.y) -= 5 * cos(player->angle);  // Move forward
		*(player->pos.x) -= 5 * sin(player->angle);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S)) {
		*(player->pos.y) += 5 * cos(player->angle);  // Move backward
		*(player->pos.x) += sin(player->angle);
	}

	// Strafing (side stepping)
	if (mlx_is_key_down(mlx, MLX_KEY_A)) {
		*(player->pos.x) += 5 * cos(player->angle);  // Move left
		*(player->pos.y) -= sin(player->angle);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D)) {
		*(player->pos.x) -= 5 * cos(player->angle);  // Move right
		*(player->pos.y) += 5 * sin(player->angle);
	}
}
