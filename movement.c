/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:12:04 by isemin            #+#    #+#             */
/*   Updated: 2025/02/09 19:01:16 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "movement.h"

static t_IntPair directions(double rayDir)
{
	t_IntPair	directions;

	if (rayDir < PI / 2 || rayDir > 3 * PI / 2)
		directions.x = 1;
	else
		directions.x = -1;
	if (rayDir < PI)
		directions.y = -1;
	else
		directions.y = 1;
	return (directions);
}

void	ft_movement_input(void *param)
{
	t_World_Controller *world;

	world = (t_World_Controller *)param;
	if (mlx_is_key_down(world->window, MLX_KEY_E))
		set_h_rotation(world, -0.05);
	if (mlx_is_key_down(world->window, MLX_KEY_Q))
		set_h_rotation(world, +0.05);
	if (mlx_is_key_down(world->window, MLX_KEY_D))
		set_movement(world, (t_DoublePair){0.5 * sin(world->player->angle), 0.5 * cos(world->player->angle)});
	if (mlx_is_key_down(world->window, MLX_KEY_A))
		set_movement(world, (t_DoublePair){-0.5 * sin(world->player->angle), -0.5 * cos(world->player->angle)});
	if (mlx_is_key_down(world->window, MLX_KEY_W))
		set_movement(world, (t_DoublePair){0.5 * sin(world->player->angle + PI / 2), 0.5 * cos(world->player->angle + PI / 2)});
	if (mlx_is_key_down(world->window, MLX_KEY_S))
		set_movement(world, (t_DoublePair){0.5 * sin(world->player->angle - PI / 2), 0.5 * cos(world->player->angle - PI / 2)});
	// 		if (mlx_is_key_down(world->window, MLX_KEY_S))
	// 	set_movement(world, (t_DoublePair){0.5 * sin(world->player->angle), 0.5 * cos(world->player->angle)});
	// if (mlx_is_key_down(world->window, MLX_KEY_W))
	// 	set_movement(world, (t_DoublePair){-0.5 * sin(world->player->angle), -0.5 * cos(world->player->angle)});
	// if (mlx_is_key_down(world->window, MLX_KEY_A))
	// 	set_movement(world, (t_DoublePair){0.5 * sin(world->player->angle + PI / 2), 0.5 * cos(world->player->angle + PI / 2)});
	// if (mlx_is_key_down(world->window, MLX_KEY_D))
	// 	set_movement(world, (t_DoublePair){0.5 * sin(world->player->angle - PI / 2), 0.5 * cos(world->player->angle - PI / 2)});
	printf("player pos x: %f, y: %f\n", world->player->pos.x, world->player->pos.y);
	// adjust for walls()
}

void	set_h_rotation(t_World_Controller *world, double angle_delta)
{
	write(1, "set_h_rotation\n", 15);
	world->player->angle += angle_delta;  // Decrease angle by 1 degree in radians
		write(1, "set_h_rotation2\n", 16);
	if (world->player->angle < 0)
	{
		write(1, "set_h_rotation3\n", 16);
		world->player->angle += 2 * PI;  // Wrap around if the angle goes below 0
	}
	else if (world->player->angle >= 2 * PI)
	{
		write(1, "set_h_rotation4\n", 16);
		world->player->angle -= 2 * PI;  // Wrap around if the angle exceeds 2π
	}
	write(1, "set_rotation_last\n", 16);
}

void	set_movement(t_World_Controller *world, t_DoublePair delta_x_y)
{
	write(1, "set_movement\n", 13);
	double			angle;
	t_Collision		collision;
	t_IntPair		direction;

	angle = world->player->angle;
	direction = directions(angle);
	collision = collision_find_wall(world->mini_map, world->player, angle);
	if (collision.type == VERTICAL)
	{
		world->player->pos.x = collision.hit.x - direction.x * 0.1 * TILE_SIZE;
		world->player->pos.y += delta_x_y.y;
		world->player->pos = check_other_wall(world->mini_map, world->player->pos, direction, HORIZONTAL);
	}
	else if (collision.type == HORIZONTAL)
	{
		world->player->pos.y = collision.hit.y - direction.y * 0.1 * TILE_SIZE;
		world->player->pos.x += delta_x_y.x;
		world->player->pos = check_other_wall(world->mini_map, world->player->pos, direction, VERTICAL);
	}
	else
	{
		world->player->pos.x += delta_x_y.x;
		world->player->pos.y += delta_x_y.y;
	}
}

t_DoublePair check_other_wall(t_mini_map *mini_map, t_DoublePair pos, t_IntPair direction, int caller)
{
	if (is_wall(mini_map, pos, direction, caller) == false) {
			return (pos);
	}
	if (caller == VERTICAL)
	{	
		if (direction.x == 1)
			pos.x = ceil_map(pos.x) - 0.1 * TILE_SIZE;
		else // left direction
			pos.x = floor_map(pos.x) + 0.1 * TILE_SIZE;
	}
	else
	{
		if (direction.y == -1)
			pos.y = floor_map(pos.y) + 0.1 * TILE_SIZE;
		else // down direction
			pos.y = ceil_map(pos.y) - 0.1 * TILE_SIZE;
	}
	return (pos);
}
