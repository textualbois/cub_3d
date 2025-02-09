/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:41:00 by isemin            #+#    #+#             */
/*   Updated: 2025/02/09 19:36:52 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extra_math.h"

double	distance(t_DoublePair a, t_DoublePair b)
{
	return (sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

double	ceil_map(double x)
{
	return ((((int)x / TILE_SIZE) + 1) * TILE_SIZE);
}

double	floor_map(double x)
{
	return (((int)x / TILE_SIZE) * TILE_SIZE);
}
