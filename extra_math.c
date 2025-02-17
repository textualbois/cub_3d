/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:41:00 by isemin            #+#    #+#             */
/*   Updated: 2025/02/17 14:03:19 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extra_math.h"
#include "stdio.h"

double	distance(t_DoublePair a, t_DoublePair b)
{
	double	result;

	result = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	//printf("[DEBUG] distance: a=(%.2f, %.2f), b=(%.2f, %.2f) -> result=%.2f\n",
	//	a.x, a.y, b.x, b.y, result);
	return (result);
}

double	ceil_map(double x)
{
	double	result;

	result = ((((int)x / TILE_SIZE) + 1) * TILE_SIZE);
//	printf("[DEBUG] ceil_map: x=%.2f -> result=%.2f\n", x, result);
	return (result);
}

double	floor_map(double x)
{
	double	result;

	result = (((int)x / TILE_SIZE) * TILE_SIZE);
//	printf("[DEBUG] floor_map: x=%.2f -> result=%.2f\n", x, result);
	return (result);
}

t_DoublePair	add_pair(t_DoublePair a, t_DoublePair b)
{
	t_DoublePair	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	//printf("[DEBUG] add_pair: a=(%.2f, %.2f), b=(%.2f, %.2f) -> result=(%.2f, %.2f)\n", a.x, a.y, b.x, b.y, result.x, result.y);
	return (result);
}

double	normalise_radians(double angle)
{
	//printf("[DEBUG] normalise_radians: initial angle=%.6f\n", angle);
	while (angle < 0)
		angle += 2 * PI;
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	//printf("[DEBUG] normalise_radians: normalised angle=%.6f\n", angle);
	return (angle);
}