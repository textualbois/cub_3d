/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_character.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:37 by isemin            #+#    #+#             */
/*   Updated: 2025/02/15 20:07:47 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "stdio.h"
#include "extra_math.h"

void ft_color_mini_character(mlx_image_t *player, int color)
{
	uint32_t	x = 0;// + 2;
	uint32_t		y = 0;// + 2;

	while (x < player->width)//5 + 2)
	{
		y = 0;// + 2;
		while (y < player->height)//5 + 2)
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

	centre.x = (double)character->width / 2;
	centre.y = (double)character->height / 2;
	offset = 2; // (character->width - player->size.x) / 2;
	// Color the main body of the character
	for (iter.x = offset; iter.x < offset + player->size.x; iter.x++) {
		for (iter.y = offset; iter.y < offset + player->size.y; iter.y++) {
			mlx_put_pixel(character, iter.x, iter.y, color);
		}
	}
	write(1, "colored_mini_character\n", 23);

	// Color the direction of the character
	end.x = centre.x + (player->size.x) * cos(player->angle.x);
	end.y = centre.y - (player->size.y) * sin(player->angle.x);
	ft_color_line(character, color, centre, end);
	write(1, "ft_color_mini_character_direction_end\n", 38);
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
	printf("size of line = %f\n", distance(start, end));
	printf("size of image = %d\n", img->width);

// }	while (fabs(iter.x - end.x) > 0.5 || fabs(iter.y - end.y) > 0.5)
	while ((int)iter.x != (int)end.x && (int)iter.y != (int)end.y)
	{
		printf("coloring points %f %f\n", iter.x, iter.y);
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
	mlx_put_pixel(img, (int)end.x, (int)end.y, color);
}
