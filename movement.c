/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:12:04 by isemin            #+#    #+#             */
/*   Updated: 2025/02/09 10:53:27 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define PLAYER_COLLISION_HALF_WIDTH (5.0 / 4.0)
#define PLAYER_COLLISION_HALF_HEIGHT (5.0 / 4.0)

#include "movement.h"

static int	is_collision(t_World_Controller *world, double new_x, double new_y)
{
	int	tile_x;
	int	tile_y;

	tile_x = (int)(new_x / TILE_SIZE);
	tile_y = (int)(new_y / TILE_SIZE);
	if (tile_x < 0 || tile_y < 0 || tile_x >= world->mini_map->size_int.x
		|| tile_y >= world->mini_map->size_int.y)
		return (1); // Выход за пределы карты
	if (world->mini_map->map[tile_y][tile_x] == '1')
		return (1); // В клетке стоит стена
	return (0);
}

void	ft_movement_input(void *param)
{
	t_World_Controller	*world;

	world = (t_World_Controller *)param;
	if (mlx_is_key_down(world->window, MLX_KEY_E))
		set_h_rotation(world, 0.05);
	if (mlx_is_key_down(world->window, MLX_KEY_Q))
		set_h_rotation(world, -0.05);
	if (mlx_is_key_down(world->window, MLX_KEY_S))
		set_movement(world, (t_DoublePair){0.1 * cos(world->player->angle), 0.1
			* sin(world->player->angle)});
	if (mlx_is_key_down(world->window, MLX_KEY_W))
		set_movement(world, (t_DoublePair){-1 * cos(world->player->angle), -1
			* sin(world->player->angle)});
	if (mlx_is_key_down(world->window, MLX_KEY_A))
		set_movement(world, (t_DoublePair){0.1 * cos(world->player->angle + PI
				/ 2), 0.1 * sin(world->player->angle + PI / 2)});
	if (mlx_is_key_down(world->window, MLX_KEY_D))
		set_movement(world, (t_DoublePair){0.1 * cos(world->player->angle - PI
				/ 2), 0.1 * sin(world->player->angle - PI / 2)});
	printf("player pos x: %f, y: %f\n", world->player->pos.x,
		world->player->pos.y);
	// остальные обновления (например, рендер и т.п.)
}

void	set_h_rotation(t_World_Controller *world, double angle_delta)
{
	write(1, "set_h_rotation\n", 15);
	world->player->angle += angle_delta;
	write(1, "set_h_rotation2\n", 16);
	if (world->player->angle < 0)
	{
		write(1, "set_h_rotation3\n", 16);
		world->player->angle += 2 * PI;
	}
	else if (world->player->angle >= 2 * PI)
	{
		write(1, "set_h_rotation4\n", 16);
		world->player->angle -= 2 * PI;
	}
	write(1, "set_rotation_last\n", 16);
}

void	set_movement(t_World_Controller *world, t_DoublePair delta)
{
	double	new_x;
	double	new_y;

	write(1, "set_movement\n", 13);
	new_x = world->player->pos.x + delta.x;
	new_y = world->player->pos.y + delta.y;
	// Проверяем перемещение по оси X
	if (!is_collision(world, new_x, world->player->pos.y))
	{
		world->player->pos.x = new_x;
	}
	// Проверяем перемещение по оси Y
	if (!is_collision(world, world->player->pos.x, new_y))
	{
		world->player->pos.y = new_y;
	}
}
