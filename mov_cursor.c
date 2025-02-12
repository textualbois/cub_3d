/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mov_cursor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:56:57 by isemin            #+#    #+#             */
/*   Updated: 2025/02/12 23:17:55 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "movement.h"

void	ft_cursor_input(double x_pos, double y_pos, void *param)
{
	static t_DoublePair	prev_pos = {0, 0};
	t_World_Controller	*world;
	t_DoublePair		delta;

	world = (t_World_Controller *)param;
	if (prev_pos.x == 0 && prev_pos.y == 0) {
		prev_pos.x = x_pos;
		prev_pos.y = y_pos;
		return;
	}
	delta.x = (x_pos - prev_pos.x) * 0.0025;
	delta.y = (y_pos - prev_pos.y) * 0.0025;
	prev_pos.x = x_pos;
	prev_pos.y = y_pos;
	set_h_rotation(world, -delta.x);
	set_v_rotation(world, -delta.y);

}
