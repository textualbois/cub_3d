/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:12:04 by isemin            #+#    #+#             */
/*   Updated: 2025/02/20 13:51:33 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #define PLAYER_COLLISION_HALF_WIDTH (5.0 / 2.0)
// #define PLAYER_COLLISION_HALF_HEIGHT (5.0 / 2.0)

#include "movement.h"

static void	set_corners(double corners[4][2], double center_x, double center_y)
{
	double	offset;

	offset = 2;
	corners[0][0] = center_x - offset;
	corners[0][1] = center_y - offset;
	corners[1][0] = center_x;
	corners[1][1] = center_y;
	corners[2][0] = center_x - offset;
	corners[2][1] = center_y;
	corners[3][0] = center_x;
	corners[3][1] = center_y;
}

static int	check_collision(t_World_Controller *world, double corners[4][2])
{
	int	i;
	int	tile_x;
	int	tile_y;

	i = 0;
	while (i < 4)
	{
		tile_x = (int)(corners[i][0] / TILE_SIZE);
		tile_y = (int)(corners[i][1] / TILE_SIZE);
		if (tile_x < 0 || tile_y < 0 || tile_x >= world->mini_map->size_int.x
			|| tile_y >= world->mini_map->size_int.y)
			return (1);
		if (world->mini_map->map[tile_y][tile_x] == '1')
			return (1);
		i++;
	}
	return (0);
}

static int	hitbox_collision(t_World_Controller *world, double center_x,
		double center_y)
{
	double	corners[4][2];

	set_corners(corners, center_x, center_y);
	return (check_collision(world, corners));
}

static void	ft_rotation_input(t_World_Controller *world)
{
	if (mlx_is_key_down(world->window, MLX_KEY_E)
		|| mlx_is_key_down(world->window, MLX_KEY_RIGHT))
		set_h_rotation(world, -0.05);
	if (mlx_is_key_down(world->window, MLX_KEY_Q)
		|| mlx_is_key_down(world->window, MLX_KEY_LEFT))
		set_h_rotation(world, +0.05);
	if (mlx_is_key_down(world->window, MLX_KEY_UP))
		set_v_rotation(world, 0.05);
	if (mlx_is_key_down(world->window, MLX_KEY_DOWN))
		set_v_rotation(world, -0.05);
}

void	ft_movement_input(void *param)
{
	t_World_Controller	*world;

	world = (t_World_Controller *)param;
	if (mlx_is_key_down(world->window, MLX_KEY_D))
		set_movement(world, (t_DoublePair){sin(world->player->angle.x),
			cos(world->player->angle.x)});
	if (mlx_is_key_down(world->window, MLX_KEY_A))
		set_movement(world, (t_DoublePair){-sin(world->player->angle.x),
			-cos(world->player->angle.x)});
	if (mlx_is_key_down(world->window, MLX_KEY_W))
		set_movement(world, (t_DoublePair){sin(world->player->angle.x + PI / 2),
			cos(world->player->angle.x + PI / 2)});
	if (mlx_is_key_down(world->window, MLX_KEY_S))
		set_movement(world, (t_DoublePair){sin(world->player->angle.x - PI / 2),
			cos(world->player->angle.x - PI / 2)});
}

void	ft_handle_input(void *param)
{
	t_World_Controller	*world;

	world = (t_World_Controller *)param;
	ft_rotation_input(world);
	ft_movement_input(world);
}

void	set_h_rotation(t_World_Controller *world, double angle_delta)
{
	world->player->angle.x += angle_delta;
	if (world->player->angle.x < 0)
		world->player->angle.x += 2 * PI;
	else if (world->player->angle.x >= 2 * PI)
		world->player->angle.x -= 2 * PI;
}

void	set_v_rotation(t_World_Controller *world, double angle_delta)
{
	world->player->angle.y += angle_delta;
	if (world->player->angle.y < -PI / 2)
		world->player->angle.y = -PI / 2;
	if (world->player->angle.y > PI / 2)
		world->player->angle.y = PI / 2;
}

void	set_movement(t_World_Controller *world, t_DoublePair delta)
{
	double	new_x;
	double	new_y;

	new_x = world->player->pos.x + delta.x;
	new_y = world->player->pos.y;
	if (!hitbox_collision(world, new_x, new_y))
		world->player->pos.x = new_x;
	new_x = world->player->pos.x;
	new_y = world->player->pos.y + delta.y;
	if (!hitbox_collision(world, new_x, new_y))
	{
		world->player->pos.y = new_y;
	}
}
