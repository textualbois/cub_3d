/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 06:35:51 by isemin            #+#    #+#             */
/*   Updated: 2025/02/18 17:44:57 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <stdio.h>

void	ray_result(t_renderData *data, t_DoublePair hit, int direction,
		int hit_type)
{
	if (!data)
	{
		// printf("[ERROR] ray_result: data is NULL\n");
		return ;
	}
	data->hit = hit;
	// printf("[DEBUG] ray_result: hit=(%.2f, %.2f), direction=%d, hit_type=%d\n",
	// 	hit.x, hit.y, direction, hit_type);
	if (hit_type == VERTICAL)
	{
		if (direction == -1)
		{
			data->txtr_code = WEST;
			data->txtr.x = ceil(hit.y / TILE_SIZE) * TILE_SIZE - hit.y;
		}
		else
		{
			data->txtr_code = EAST;
			data->txtr.x = hit.y - floor(hit.y / TILE_SIZE) * TILE_SIZE;
		}
	}
	else
	{
		if (direction == -1)
		{
			data->txtr_code = NORTH;
			data->txtr.x = hit.x - floor(hit.x / TILE_SIZE) * TILE_SIZE;
		}
		else
		{
			data->txtr_code = SOUTH;
			data->txtr.x = ceil(hit.x / TILE_SIZE) * TILE_SIZE - hit.x;
		}
	}
}

static t_IntPair	directions(double rayDir)
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

void	ray_find_wall(t_mini_map *mini_map, t_character *player,
		t_renderData *data)
{
	t_DoublePair	vertical_hit;
	t_DoublePair	horizontal_hit;
	t_IntPair		direction;

	direction = directions(data->rayDir);
	vertical_hit = ray_find_vertical_hit(mini_map, player, data->rayDir,
			direction);
	horizontal_hit = ray_find_horizontal_hit(mini_map, player, data->rayDir,
			direction);
	if (vertical_hit.x == -1)
		ray_result(data, horizontal_hit, direction.y, HORIZONTAL);
	else if (horizontal_hit.x == -1)
		ray_result(data, vertical_hit, direction.x, VERTICAL);
	else if (distance(player->pos, vertical_hit) < distance(player->pos,
			horizontal_hit))
		ray_result(data, vertical_hit, direction.x, VERTICAL);
	else
		ray_result(data, horizontal_hit, direction.y, HORIZONTAL);
}

static int	check_hit_bounds(t_DoublePair *hit, t_mini_map *mini_map)
{
	if (!hit || !mini_map)
	{
		// printf("[ERROR] check_hit_bounds: NULL pointer detected\n");
		return (false);
	}
	if (hit->x < 0 || hit->x >= mini_map->size.x || hit->y < 0
		|| hit->y >= mini_map->size.y)
	{
		// printf("[WARNING] check_hit_bounds: hit out of bounds (%.2f, %.2f)\n",
		// 	hit->x, hit->y);
		return (false);
	}
	return (true);
}

t_DoublePair	ray_find_vertical_hit(t_mini_map *mini_map, t_character *player,
		double rayDir, t_IntPair direction)
{
	t_DoublePair	hit;

	if (direction.x == 1)
	{
		hit.x = ceil_map(player->pos.x);
	}
	else
	{
		hit.x = floor_map(player->pos.x);
	}
	hit.y = player->pos.y - (hit.x - player->pos.x) * tan(rayDir);
	if (check_hit_bounds(&hit, mini_map) == false)
		return ((t_DoublePair){-1, -1});
	while (is_wall(mini_map, hit, direction, VERTICAL) == false)
	{
		increment_vertical(&hit, direction.x, rayDir);
		if (check_hit_bounds(&hit, mini_map) == false)
			return ((t_DoublePair){-1, -1});
	}
	return (hit);
}

t_DoublePair	ray_find_horizontal_hit(t_mini_map *mini_map,
		t_character *player, double rayDir, t_IntPair direction)
{
	t_DoublePair	hit;

	if (direction.y == -1)
		hit.y = floor_map(player->pos.y);
	else
		hit.y = ceil_map(player->pos.y);
	hit.x = player->pos.x - (hit.y - player->pos.y) / tan(rayDir);
	if (check_hit_bounds(&hit, mini_map) == false)
		return ((t_DoublePair){-1, -1});
	while (is_wall(mini_map, hit, direction, HORIZONTAL) == false)
	{
		increment_horizontal(&hit, direction.y, rayDir);
		if (check_hit_bounds(&hit, mini_map) == false)
			return ((t_DoublePair){-1, -1});
	}
	return (hit);
}

bool	is_wall(t_mini_map *mini_map, t_DoublePair hit, t_IntPair direction,
		int caller)
{
	t_IntPair	modifier;
	int			map_x;
	int			map_y;

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
	/* Вычисляем индексы в карте с учетом смещения */
	map_x = modifier.x + ((int)hit.x / TILE_SIZE);
	map_y = modifier.y + ((int)hit.y / TILE_SIZE);
	/* Проверяем, что индексы не выходят за пределы карты */
	if (map_x < 0 || map_x >= mini_map->size.x || map_y < 0
		|| map_y >= mini_map->size.y)
	{
		// printf("[WARNING] is_wall: computed index out of bounds (%d, %d)\n",
		// 	map_x, map_y);
		/* Если индекс вне границ, можно считать,
			что за пределами карты стена */
		return (true);
	}
	/* Если на найденной позиции стоит '1', значит это стена */
	if (mini_map->map[map_y][map_x] == '1')
		return (true);
	return (false);
}
