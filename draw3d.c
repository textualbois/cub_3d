/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:32:15 by isemin            #+#    #+#             */
/*   Updated: 2025/02/15 17:01:20 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "draw_textures.h"

double	compute_texture_x(t_character *player, t_ray ray)
{
	double	wallX;

	if (ray.side == 0)
		wallX = player->pos.y + ray.perpWallDist * ray.rayDirY;
	else
		wallX = player->pos.x + ray.perpWallDist * ray.rayDirX;
	wallX -= floor(wallX);
	if ((ray.side == 0 && ray.rayDirX < 0) || (ray.side == 1
			&& ray.rayDirY > 0))
		wallX = 1.0 - wallX;
	printf("[DEBUG] compute_texture_x: wallX = %f\n", wallX);
	return (wallX);
}

#include "draw_textures.h"

void	draw_textured_vertical_line(mlx_image_t *img, t_line line,
		t_tex_line tex_line)
{
	int			lineHeight;
	int			y;
	double		relativeY;
	int			texY;
	int			texX;
	uint32_t	*texPixels;
	uint32_t	color;

	lineHeight = line.bottom - line.top;
	y = line.top;
	while (y < line.bottom)
	{
		relativeY = (double)(y - line.top) / lineHeight;
		texY = (int)(relativeY * tex_line.texture->height);
		if (texY < 0)
			texY = 0;
		if (texY >= (int)tex_line.texture->height)
			texY = tex_line.texture->height - 1;
		texX = (int)(tex_line.textureX * tex_line.texture->width);
		if (texX < 0)
			texX = 0;
		if (texX >= (int)tex_line.texture->width)
			texX = tex_line.texture->width - 1;
		texPixels = (uint32_t *)tex_line.texture->pixels;
		if (!texPixels)
		{
			printf("[ERROR] draw_textured_vertical_line: texture->pixels is NULL!\n");
			return ;
		}
		color = texPixels[texY * tex_line.texture->width + texX];
		mlx_put_pixel(img, line.x, y, color);
		y++;
	}
}

void	draw3d(t_draw3d_params *params, t_ray ray, t_World_Controller *world)
{
	double		lineH;
	mlx_image_t	*texture;
	double		textureX;
	t_line		line;
	t_tex_line	tex_line;

	int top, bottom;
	double pitch, vertical_offset;
	/* Используем pitch из игрока */
	pitch = world->player->angle.x;
	/* Вычисляем высоту столбца стены */
	lineH = ((double)TILE_SIZE * params->world3d->height) / ray.perpWallDist;
	/* Вычисляем вертикальное смещение */
	vertical_offset = (double)params->world3d->height / (4.0 * MAX_PITCH)
		* pitch;
	top = (int)(((double)params->world3d->height - lineH) / 2.0
			+ vertical_offset);
	bottom = top + (int)lineH;
	if (top < 0)
	{
		printf("[DEBUG] Clipping top from %d to 0\n", top);
		top = 0;
	}
	if (bottom > (int)params->world3d->height)
	{
		printf("[DEBUG] Clipping bottom from %d to %d\n", bottom,
			params->world3d->height);
		bottom = params->world3d->height;
	}
	/* Выбор текстуры по стороне удара */
	if (ray.side == 0)
	{
		if (ray.rayDirX > 0)
			texture = world->texture_we;
		else
			texture = world->texture_ea;
	}
	else
	{
		if (ray.rayDirY > 0)
			texture = world->texture_no;
		else
			texture = world->texture_so;
	}
	if (!texture)
	{
		printf("[ERROR] draw3d: Selected texture is NULL!\n");
		return ;
	}
	printf("[DEBUG] draw3d: Selected texture=%p, width=%u, height=%u\n",
		texture, texture->width, texture->height);
	textureX = compute_texture_x(params->player, ray);
	printf("[DEBUG] draw3d: textureX = %f\n", textureX);
	line.x = params->x;
	line.top = top;
	line.bottom = bottom;
	tex_line.texture = texture;
	tex_line.textureX = textureX;
	printf("[DEBUG] draw3d: Drawing textured vertical line at x=%d, top=%d, bottom=%d\n", line.x, line.top, line.bottom);
	draw_textured_vertical_line(params->world3d, line, tex_line);
}
