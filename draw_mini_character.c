/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_character.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:37 by isemin            #+#    #+#             */
/*   Updated: 2025/01/26 19:53:04 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "character.h"

void ft_color_mini_character(mlx_image_t *player, int color)
{
	int x = 0;
	int y = 0;

	while (x < 5)
	{
		y = 0;
		while (y < 5)
		{
			mlx_put_pixel(player, x, y, color);
			y++;
		}
		x++;
	}
}

void ft_color_mini_character_direction(mlx_image_t *character, int color, t_character *player)
{
	t_DoublePair	centre;
	int				offset;
	t_IntPair		iter;
	t_DoublePair	end;

	centre.x = character->width / 2;
	centre.y = character->height / 2;
	offset = 2; // (character->width - player->size.x) / 2;
	// Color the main body of the character
	for (iter.x = offset; iter.x < offset + player->size.x; iter.x++) {
		for (iter.y = offset; iter.y < offset + player->size.y; iter.y++) {
			mlx_put_pixel(character, iter.x, iter.y, color);
		}
	}

	// Color the direction of the character
	end.x = player->pos.x + player->size.x / 2 * cos(player->angle);
	end.y = player->pos.y + player->size.y / 2 * sin(player->angle);
	ft_color_line(character, color, player->pos, end);
}

void	ft_color_line(mlx_image_t *img, int color, t_DoublePair start, t_DoublePair end)
{
	t_DoublePair	delta;
	t_IntPair		sign;
	t_DoublePair	error;
	t_DoublePair	iter;

	delta.x = fabs(end.x - start.x);
	delta.y = fabs(end.y - start.y);
	sign.x = start.x < end.x ? 1 : -1;
	sign.y = start.y < end.y ? 1 : -1;
	error.x = delta.x - delta.y;
	iter = start;
	//while (fabs(iter.x - end.x) > 0.5 || fabs(iter.y - end.y) > 0.5)
	while (iter.x <= end.x * sign.x || iter.y <= end.y * sign.y)
	{
		mlx_put_pixel(img, (int)iter.x, (int)iter.y, color);
		error.y = error.x * 2;
		if (error.y > -delta.y)
		{
			error.x -= delta.y;
			iter.x += sign.x;
		}
		if (error.y < delta.x)
		{
			error.x += delta.x;
			iter.y += sign.y;
		}
	}
	//mlx_put_pixel(img, (int)end.x, (int)end.y, color);
}
