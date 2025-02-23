/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray_mmap2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:32:38 by vmamoten          #+#    #+#             */
/*   Updated: 2025/02/23 19:33:34 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	draw_line_step(t_IntPair *start, t_IntPair direction, t_IntPair d,
		int *err)
{
	int	e2;

	e2 = 2 * (*err);
	if (e2 >= d.y)
	{
		*err += d.y;
		start->x += direction.x;
	}
	if (e2 <= d.x)
	{
		*err += d.x;
		start->y += direction.y;
	}
}
