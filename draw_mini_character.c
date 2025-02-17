/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_character.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:37 by isemin            #+#    #+#             */
/*   Updated: 2025/02/17 12:17:47 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "extra_math.h"
#include "stdio.h"

void	ft_color_mini_character(mlx_image_t *player, int color)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	y = 0;
	while (x < player->width)
	{
		y = 0;
		while (y < player->height)
		{
			mlx_put_pixel(player, x, y, color);
			y++;
		}
		x++;
	}
}

void	ft_color_mini_character_direction(mlx_image_t *character, int color,
		t_character *player)
{
	t_DoublePair	centre;
	int				offset;
	t_IntPair		iter;
	t_DoublePair	end;

	centre.x = (double)character->width / 2;
	centre.y = (double)character->height / 2;
	offset = 2;
	iter.x = offset;
	while (iter.x < offset + player->size.x)
	{
		iter.y = offset;
		while (iter.y < offset + player->size.y)
		{
			mlx_put_pixel(character, iter.x, iter.y, color);
			iter.y++;
		}
		iter.x++;
	}
	end.x = centre.x + (player->size.x) * cos(player->angle.x);
	end.y = centre.y - (player->size.y) * sin(player->angle.x);
	ft_color_line(character, color, centre, end);
}

void	ft_bresenham_init(t_line_params *params, t_DoublePair start,
		t_DoublePair end)
{
	params->delta.x = fabs(end.x - start.x);
	params->delta.y = fabs(end.y - start.y);
	if (start.x < end.x)
		params->sign.x = 1;
	else
		params->sign.x = -1;
	if (start.y < end.y)
		params->sign.y = 1;
	else
		params->sign.y = -1;
	params->error.x = params->delta.x - params->delta.y;
	params->iter = start;
}

void	ft_draw_line(mlx_image_t *img, int color, t_DoublePair end,
		t_line_params *params)
{
	while ((int)params->iter.x != (int)end.x
		|| (int)params->iter.y != (int)end.y)
	{
		mlx_put_pixel(img, (int)params->iter.x, (int)params->iter.y, color);
		params->error.y = params->error.x * 2;
		if (params->error.y > -params->delta.y)
		{
			params->error.x -= params->delta.y;
			params->iter.x += params->sign.x;
		}
		if (params->error.y < params->delta.x)
		{
			params->error.x += params->delta.x;
			params->iter.y += params->sign.y;
		}
	}
	mlx_put_pixel(img, (int)end.x, (int)end.y, color);
}

void	ft_color_line(mlx_image_t *img, int color, t_DoublePair start,
		t_DoublePair end)
{
	t_line_params	params;

	ft_bresenham_init(&params, start, end);
	ft_draw_line(img, color, end, &params);
}
