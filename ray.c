/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 06:35:51 by isemin            #+#    #+#             */
/*   Updated: 2025/02/13 16:12:20 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <stdio.h>

// static void print_map_hit(t_mini_map *map, t_DoublePair hit)
// {
// 	int x, y;

// 	y = 0;
// 	x = 0;
// 	printf("Y\\X");
// 	while (x < map->size_int.x)
// 	{
// 		printf("|%02d|", x);
// 		x++;

// 	}
// 	printf("\n");
// 	x = 0;
// 	while (x < map->size_int.x)
// 	{
// 		printf("____");
// 		x++;
// 	}
// 	printf("\n");

// 	y = 0;
// 	while (y < map->size_int.y)
// 	{
// 		printf("%02d|", y);
// 		x = 0;
// 		while (x < map->size_int.x)
// 		{
// 			if (y == (int)hit.y / TILE_SIZE && x == (int)hit.x / TILE_SIZE)
// 				printf(" [%c]", map->map[y][x]);
// 			else
// 				printf("  %c ", map->map[y][x]);
// 			x++;
// 		}
// 		printf("\n");
// 		y++;
// 	}
// 	fflush(stdout);
// }

// static int angle_to_degree(double angle)
// {
// 	return (angle * 180 / PI);
// }

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

t_DoublePair	ray_find_wall(t_mini_map *mini_map, t_character *player, double rayDir)
{
	t_DoublePair	vertical_hit;
	t_DoublePair	horizontal_hit;
	t_IntPair		depth;
	t_IntPair		direction;

	direction = directions(rayDir);
	// printf("checking direction %f, which is %i degrees\n", rayDir, angle_to_degree(rayDir));
	depth.x = 0;
	depth.y = 0;
	vertical_hit = ray_find_vertical_hit(mini_map, player, rayDir, direction);
	horizontal_hit = ray_find_horizontal_hit(mini_map, player, rayDir, direction);
	if (vertical_hit.x == -1)
		 return (horizontal_hit);
	if (horizontal_hit.x == -1)
		return (vertical_hit);
	if (distance(player->pos, vertical_hit) < distance(player->pos, horizontal_hit))
		return (vertical_hit);
	return (horizontal_hit);
}

static int check_hit_bounds(t_DoublePair *hit, t_mini_map *mini_map)
{
	if (hit->x < 0 || hit->x >= mini_map->size.x || hit->y < 0 || hit->y >= mini_map->size.y)
		return (false);
	return (true);
}

t_DoublePair	ray_find_vertical_hit(t_mini_map *mini_map, t_character *player, double rayDir, t_IntPair direction)
{
	t_DoublePair	hit;

	// right direction
	// if (rayDir < PI / 2 || rayDir > 3 * PI / 2) {
	if (direction.x == 1) {
		hit.x = ceil_map(player->pos.x);
	} else { // left direction
		hit.x = floor_map(player->pos.x);
	}

	// printf("checking direction %f, which is %i degrees\n", rayDir, angle_to_degree(rayDir));
	hit.y = player->pos.y - (hit.x - player->pos.x) * tan(rayDir);

	// return (hit);
	// printf("pos x: %f, y: %f. hit x: %f , hit.y %f\n", player->pos.x, player->pos.y, hit.x, hit.y);
	if (check_hit_bounds(&hit, mini_map) == false)
		return ((t_DoublePair){-1, -1});
	while (is_wall(mini_map, hit, direction, VERTICAL) == false) {
		// printf("checking direction %f, which is %i degrees\n", rayDir, angle_to_degree(rayDir));
		increment_vertical(&hit, direction.x, rayDir);
		if (check_hit_bounds(&hit, mini_map) == false)
			return ((t_DoublePair){-1, -1});
	}
	return (hit);
}

t_DoublePair	ray_find_horizontal_hit(t_mini_map *mini_map, t_character *player, double rayDir, t_IntPair direction)
{
	t_DoublePair	hit;

	// up direction
	if (direction.y == -1)
		hit.y = floor_map(player->pos.y);
	else // down direction
		hit.y = ceil_map(player->pos.y);
	hit.x = player->pos.x - (hit.y - player->pos.y) / tan(rayDir);
	//return (hit);
	if (check_hit_bounds(&hit, mini_map) == false)
		return ((t_DoublePair){-1, -1});
	while (is_wall(mini_map, hit, direction, HORIZONTAL) == false) {
		// printf("checking direction %f, which is %i degrees\n", rayDir, angle_to_degree(rayDir));
		increment_horizontal(&hit, direction.y, rayDir);
		if (check_hit_bounds(&hit, mini_map) == false)
			return ((t_DoublePair){-1, -1});
	}
	return (hit);
}

bool	is_wall(t_mini_map *mini_map, t_DoublePair hit, t_IntPair direction, int caller)
{
	// print_map_hit(mini_map, hit);
	t_IntPair	modifier;
	// (void)caller;
	// (void)direction;
	modifier.x = 0;
	modifier.y = 0;
	if (direction.x == 1)
		modifier.x = 0;
	else if (caller == VERTICAL)
		modifier.x = -1;
	if (direction.y == 1)
		modifier.y = 0;
	else if (caller == HORIZONTAL)
		modifier.y = -1;

	if (mini_map->map[modifier.y + (int)hit.y / TILE_SIZE][modifier.x + (int)hit.x / TILE_SIZE] == '1')
	{
		// printf("WALL FOUND !!!\n");
		return (true);
	}
	return (false);
}

// static t_IntPair directions(double rayDir)
// {
// 	t_IntPair	directions;

// 	if (rayDir < PI / 2 || rayDir > 3 * PI / 2)
// 		directions.x = 1;
// 	else
// 		directions.x = -1;
// 	if (rayDir < PI)
// 		directions.y = -1;
// 	else
// 		directions.y = 1;
// 	return (directions);
// }