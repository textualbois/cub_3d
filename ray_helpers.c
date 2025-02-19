/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:03:39 by isemin            #+#    #+#             */
/*   Updated: 2025/02/19 18:28:42 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

void	increment_vertical(t_DoublePair *hit, int direction, double rayDir)
{
	hit->x += direction * TILE_SIZE;
	hit->y -= direction * TILE_SIZE * tan(rayDir);
}

void	increment_horizontal(t_DoublePair *hit, int direction, double rayDir)
{
	hit->y += direction * TILE_SIZE;
	hit->x -= direction * TILE_SIZE / tan(rayDir);
}

t_IntPair	box_behind_border(t_DoublePair real, int mapHeight, int l_r,
		int u_d)
{
	t_IntPair	map;

	map.x = (int)real.x / TILE_SIZE;
	map.y = mapHeight - 1 - (int)(real.y / TILE_SIZE);
	if (l_r == -1)
		map.x--;
	if (u_d == -1)
		map.y++;
	return (map);
}
