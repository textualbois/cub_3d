/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 06:35:51 by isemin            #+#    #+#             */
/*   Updated: 2025/01/29 10:23:26 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_DoublePair	ray_find_wall(t_World_Controller *world, double rayDir)
{
	t_DoublePair	vertical_hit;
	t_DoublePair	horizontal_hit;
	t_IntPair		depth;

	depth.x = 0;
	depth.y = 0;
	vertical_hit = ray_find_vertical_hit(world, rayDir, &depth.y);
	horizontal_hit = ray_find_horizontal_hit(world, rayDir, &depth.x);
	if (depth.x < depth.y)
		return (horizontal_hit);
	return (vertical_hit);
}

t_DoublePair	ray_find_vertical_hit(t_World_Controller *world, double rayDir, int *depth)
{
	t_DoublePair	hit;
	int				direction;

	// right direction
	if (rayDir < PI / 2 || rayDir > 3 * PI / 2) {
		hit.x = ceil_map(world->player->pos.x);
		direction = 1;
	} else {
		hit.x = floor_map(world->player->pos.x);
		direction = -1;
	}
	hit.y = world->player->pos.y + (hit.x - world->player->pos.x) * tan(rayDir);
	while (!is_wall(world, hit)) { // can add depth check <= LOD
		increment_vertical(&hit, direction);
		(*depth)++;
	}

	return (hit);
}

t_DoublePair	ray_find_horizontal_hit(t_World_Controller *world, double rayDir, int *depth)
{
	t_DoublePair	hit;
	t_DoublePair	next;

	// up direction
	if (rayDir > 0 && rayDir < PI) {
		hit.y = floor(world->player->pos.y) + TILE_SIZE;
		hit.x = world->player->pos.x + (hit.y - world->player->pos.y) / tan(rayDir);
	} else {
		hit.y = floor(world->player->pos.y);
		hit.x = world->player->pos.x + (hit.y - world->player->pos.y) / tan(rayDir);
	}


	return (hit);
}

bool	is_wall(t_World_Controller *world, t_DoublePair hit)
{
	// if (hit.x < 0 || hit.x >= world->size.x || hit.y < 0 || hit.y >= world->size.y)
	// 	return (true);
	if (world->map[(int)hit.y][(int)hit.x] == 1)
		return (true);
	return (false);
}
