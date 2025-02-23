/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:43:30 by vmamoten          #+#    #+#             */
/*   Updated: 2025/02/23 19:46:34 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "movement.h"

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

int	hitbox_collision(t_World_Controller *world, double center_x,
		double center_y)
{
	double	corners[4][2];

	set_corners(corners, center_x, center_y);
	return (check_collision(world, corners));
}
