/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:41:00 by isemin            #+#    #+#             */
/*   Updated: 2025/02/19 17:30:31 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extra_math.h"
#include "stdio.h"

double	distance(t_DoublePair a, t_DoublePair b)
{
	double	result;

	result = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	return (result);
}

double	ceil_map(double x)
{
	double	result;

	result = ((((int)x / TILE_SIZE) + 1) * TILE_SIZE);
	return (result);
}

double	floor_map(double x)
{
	double	result;

	result = (((int)x / TILE_SIZE) * TILE_SIZE);
	return (result);
}

t_DoublePair	add_pair(t_DoublePair a, t_DoublePair b)
{
	t_DoublePair	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return (result);
}

double	normalise_radians(double angle)
{
	while (angle < 0)
		angle += 2 * PI;
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}
