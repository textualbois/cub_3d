/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:21:17 by vmamoten          #+#    #+#             */
/*   Updated: 2025/02/23 19:30:19 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <stdio.h>

void	set_vertical_texture(t_renderData *data, t_DoublePair hit,
		int direction)
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

void	set_horizontal_texture(t_renderData *data, t_DoublePair hit,
		int direction)
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

void	ray_result(t_renderData *data, t_DoublePair hit, int direction,
		int hit_type)
{
	if (!data)
		return ;
	data->hit = hit;
	if (hit_type == VERTICAL)
		set_vertical_texture(data, hit, direction);
	else
		set_horizontal_texture(data, hit, direction);
}
