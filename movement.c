#include "movement.h"

void	ft_movement_input(void *param)
{
	t_World_Controller *world;

	world = (t_World_Controller *)param;
	if (mlx_is_key_down(world->window, MLX_KEY_Q))
		set_h_rotation(world, 1);
	if (mlx_is_key_down(world->window, MLX_KEY_E))
		set_h_rotation(world, -1);
	if (mlx_is_key_down(world->window, MLX_KEY_W))
		set_movement(world, (t_DoublePair){-5 * cos(world->player->angle), -5 * sin(world->player->angle)});
	if (mlx_is_key_down(world->window, MLX_KEY_S))
		set_movement(world, (t_DoublePair){5 * cos(world->player->angle), 5 * sin(world->player->angle)});
	if (mlx_is_key_down(world->window, MLX_KEY_A))
		set_movement(world, (t_DoublePair){5 * cos(world->player->angle + PI / 2), 5 * sin(world->player->angle + PI / 2)});
	if (mlx_is_key_down(world->window, MLX_KEY_D))
		set_movement(world, (t_DoublePair){5 * cos(world->player->angle - PI / 2), 5 * sin(world->player->angle - PI / 2)});
}

void	set_h_rotation(t_World_Controller *world, int angle_delta)
{
	world->player->angle += angle_delta;  // Decrease angle by 1 degree in radians
	if (world->player->angle < 0)
		world->player->angle += 2 * PI;  // Wrap around if the angle goes below 0
	else if (world->player->angle >= 2 * PI)
		world->player->angle -= 2 * PI;  // Wrap around if the angle exceeds 2π
}

void	set_movement(t_World_Controller *world, t_DoublePair delta_x_y)
{
	world->player->pos.x += delta_x_y.x;
	world->player->pos.y += delta_x_y.y;
}

