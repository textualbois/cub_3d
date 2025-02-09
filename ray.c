/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 06:35:51 by isemin            #+#    #+#             */
/*   Updated: 2025/02/09 21:32:51 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <stdio.h>

static void print_map_hit(t_mini_map *map, t_DoublePair hit)
{
	int x, y;

	y = 0;
	x = 0;
	printf("Y\\X");
	while (x < map->size_int.x)
	{
		printf("|%02d|", x);
		x++;

	}
	printf("\n");
	x = 0;
	while (x < map->size_int.x)
	{
		printf("____");
		x++;
	}
	printf("\n");

	y = 0;
	while (y < map->size_int.y)
	{
		printf("%02d|", y);
		x = 0;
		while (x < map->size_int.x)
		{
			if (y == (int)hit.y / TILE_SIZE && x == (int)hit.x / TILE_SIZE)
				printf(" [%c]", map->map[y][x]);
			else
				printf("  %c ", map->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	fflush(stdout);
}

static int angle_to_degree(double angle)
{
	return (angle * 180 / PI);
}

t_DoublePair	ray_find_wall(t_mini_map *mini_map, t_character *player, double rayDir)
{
	t_DoublePair	vertical_hit;
	// t_DoublePair	horizontal_hit;
	t_IntPair		depth;
	printf("checking direction %f, which is %i degrees\n", rayDir, angle_to_degree(rayDir));
	depth.x = 0;
	depth.y = 0;
	vertical_hit = ray_find_vertical_hit(mini_map, player, rayDir, &depth.y);
	// horizontal_hit = ray_find_horizontal_hit(mini_map, player, rayDir, &depth.x);
	// if ((depth.x >= 0 && depth.x < depth.y) || depth.y == -1)
		// return (horizontal_hit);
	return (vertical_hit);
}

static int check_hit_bounds(t_DoublePair *hit, t_mini_map *mini_map)
{
	if (hit->x < 0 || hit->x >= mini_map->size.x || hit->y < 0 || hit->y >= mini_map->size.y)
		return (false);
	return (true);
}

t_DoublePair	ray_find_vertical_hit(t_mini_map *mini_map, t_character *player, double rayDir, int *depth)
{
	t_DoublePair	hit;
	t_IntPair		direction;

	// right direction
	if (rayDir < PI / 2 || rayDir > 3 * PI / 2) {
		hit.x = ceil_map(player->pos.x);
		direction.x = 1;
	} else { // left direction
		hit.x = floor_map(player->pos.x);
		direction.x = -1;
	}
	if (rayDir < PI)
		direction.y = -1;
	else
		direction.y = 1;
	printf("checking direction %f, which is %i degrees\n", rayDir, angle_to_degree(rayDir));
	hit.y = player->pos.y - (hit.x - player->pos.x) * tan(rayDir);

	// return (hit);
	printf("pos x: %f, y: %f. hit x: %f , hit.y %f\n", player->pos.x, player->pos.y, hit.x, hit.y);
	if (check_hit_bounds(&hit, mini_map) == false)
	{
		*depth = -1;
		return (hit);
	}

	while (is_wall(mini_map, hit) == false) { // can add depth check <= LOD

		printf("checking direction %f, which is %i degrees\n", rayDir, angle_to_degree(rayDir));
		increment_vertical(&hit, direction, rayDir);
		if (check_hit_bounds(&hit, mini_map) == false)
		{
			*depth = -1;
			return (hit);
		}
		(*depth)++;
	}
	return (hit);
}

t_DoublePair	ray_find_horizontal_hit(t_mini_map *mini_map, t_character *player, double rayDir, int *depth)
{
	t_DoublePair	hit;
	// int				direction;

	// up direction
	if (rayDir < PI) {
		hit.y = floor_map(player->pos.y);
		// direction = -1;
	} else { // down direction
		hit.y = ceil_map(player->pos.y);
		// direction = 1;
	}
	hit.x = player->pos.x - (hit.y - player->pos.y) / tan(rayDir);
	if (check_hit_bounds(&hit, mini_map) == false)
	{
		*depth = -1;
		return (hit);
	}
	while (is_wall(mini_map, hit) == false) { // can add depth check <= LOD
		printf("checking direction %f, which is %i degrees\n", rayDir, angle_to_degree(rayDir));
		increment_horizontal(&hit, 1, rayDir);
		if (check_hit_bounds(&hit, mini_map) == false)
		{
			*depth = -1;
			return (hit);
		}
		(*depth)++;
	}
	return (hit);
}

bool	is_wall(t_mini_map *mini_map, t_DoublePair hit)
{
	print_map_hit(mini_map, hit);
	if (mini_map->map[(int)hit.y / TILE_SIZE][(int)hit.x / TILE_SIZE] == '1')
	{
		printf("WALL FOUND !!!\n");
		return (true);
	}
	return (false);
}

