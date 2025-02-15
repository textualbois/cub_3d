/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:49:48 by isemin            #+#    #+#             */
/*   Updated: 2025/02/15 17:03:33 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "draw_textures.h"

#define CEILING_COLOR 0x87CEEBFF // светло-голубой
#define FLOOR_COLOR 0x654321FF   // коричневый

static double	normalise_radians(double angle)
{
	while (angle < 0)
		angle += 2 * PI;
	while (angle >= 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

void	update_ceiling_and_floor(mlx_image_t *img, uint32_t ceiling_color,
		uint32_t floor_color, double pitch)
{
	int		height;
	int		width;
	double	vertical_offset;
	int		horizon;

	int x, y;
	height = img->height;
	width = img->width;
	vertical_offset = (double)height / (4.0 * MAX_PITCH) * pitch;
	horizon = (int)(height / 2.0 + vertical_offset);
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			if (y < horizon)
				mlx_put_pixel(img, x, y, ceiling_color);
			else
				mlx_put_pixel(img, x, y, floor_color);
		}
	}
}

void	draw_world(t_World_Controller *world)
{
	t_IntPair	miniCharImgPos;

	miniCharImgPos.x = (world->player->pos.x / world->size.x)
		* world->map_img->width - (world->miniCharacter->width / 2);
	miniCharImgPos.y = (world->player->pos.y / world->size.y)
		* world->map_img->height - (world->miniCharacter->height / 2);
	printf("char image positions x: %d, y: %d\n", miniCharImgPos.x,
		miniCharImgPos.y);
	fflush(stdout);
	mlx_image_to_window(world->window, world->world3d, 0, 0);
	mlx_image_to_window(world->window, world->map_img, world->window->width
		/ 100, world->window->height - world->map_img->height
		- world->window->height / 100);
	mlx_image_to_window(world->window, world->miniCharacter, miniCharImgPos.x,
		miniCharImgPos.y);
}

void	redraw(void *param)
{
	t_World_Controller	*world;

	world = (t_World_Controller *)param;
	write(1, "redraw\n", 7);
	centre_mini_map(world->mini_map, world->player);
	color_mini_map(world->map_img, world->mini_map);
	centre_character_img(world, world->mini_map, world->player->pos);
	update_ceiling_and_floor(world->world3d, CEILING_COLOR, FLOOR_COLOR,
		world->player->angle.x);
	raycasting(world);
	ft_color_mini_character(world->miniCharacter, 0x000000FF);
	ft_color_mini_character_direction(world->miniCharacter, 0xFF0000FF,
		world->player);
	write(1, "redraw_end\n", 11);
}

static void	compute_ray_parameters(int x, t_World_Controller *world, t_ray *ray)
{
	double			fovRadians;
	double			rayAngle;
	t_DoublePair	hit;

	fovRadians = FOV * (PI / 180.0);
	/* Изменённый расчёт: правый край – -FOV/2, левый – +FOV/2 */
	rayAngle = world->player->angle.y + (fovRadians / 2) - (fovRadians * x)
		/ world->window->width;
	rayAngle = normalise_radians(rayAngle);
	printf("[DEBUG] compute_ray_parameters: x=%d, rayAngle=%f\n", x, rayAngle);
	ray->rayDirX = cos(rayAngle);
	ray->rayDirY = sin(rayAngle);
	printf("[DEBUG] compute_ray_parameters: rayDirX=%f, rayDirY=%f\n",
		ray->rayDirX, ray->rayDirY);
	hit = ray_find_wall(world->mini_map, world->player, rayAngle);
	ray->perpWallDist = distance(world->player->pos, hit);
	printf("[DEBUG] compute_ray_parameters: perpWallDist=%f, hit=(%f, %f)\n",
		ray->perpWallDist, hit.x, hit.y);
	ray->side = (fabs(hit.x - floor(hit.x)) < fabs(hit.y
				- floor(hit.y))) ? 0 : 1;
	printf("[DEBUG] compute_ray_parameters: side=%d\n", ray->side);
}

void	raycasting(t_World_Controller *world)
{
	double			rayDir;
	t_DoublePair	hit;
	int				x;
	double			radians_increment;
	t_ray			ray;
	t_draw3d_params	params;

	printf("raycasting\n");
	radians_increment = (FOV * PI / 180) / world->window->width;
	rayDir = normalise_radians(world->player->angle.y - (FOV * PI / 180) / 2);
	x = 0;
	while (x < world->window->width)
	{
		hit = ray_find_wall(world->mini_map, world->player, rayDir);
		drawray(world->player, world->map_img, world->mini_map, hit);
		compute_ray_parameters(x, world, &ray);
		params.world3d = world->world3d;
		params.player = world->player;
		params.x = x;
		draw3d(&params, ray, world);
		/* Увеличиваем угол для следующего столбца */
		rayDir = normalise_radians(rayDir + radians_increment);
		x++;
	}
}
