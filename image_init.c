#include "world.h"

int	init_images(t_World_Controller *world, int map[])
{
	world->minimap = init_minimap(world->window, map);
	if (!world->minimap)
		return (1);
	world->miniCharacter = init_image_mini_character(world->window,
			world->player, (t_IntPair){5, 5});
	if (!world->miniCharacter)
	{
		mlx_delete_image(world->window, world->minimap);
			// is this how you handle it?
		return (1);
	}
	return (0);
}

mlx_image_t	*init_image_mini_character(mlx_t *window, t_character *player,
		t_IntPair size)
{
	mlx_image_t	*miniCharacter;

	miniCharacter = mlx_new_image(window, size.x, size.y);
	if (miniCharacter)
	{
		ft_color_mini_character_direction(miniCharacter, 0xFF0000FF,
			player->angle);
		mlx_image_to_window(window, miniCharacter, player->pos.x,
			player->pos.y);
	}
	return (miniCharacter);
}

mlx_image_t	*init_image_minimap(mlx_t *window, int map[])
{
	mlx_image_t	*minimap;
	int			x;
	int			y;
	int			mHeight;
	int			mWidth;
	int			index;

	x = 0;
	y = 0;
	mHeight = 8;
	mWidth = 8;
	// uint32_t color = 0;
	minimap = mlx_new_image(window, WIDTH, HEIGHT);
	if (!minimap)
		return (NULL);
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			index = (int)(y / (HEIGHT / mHeight)) * mWidth + (int)(x / (WIDTH
						/ mWidth));
			if (index >= 0 && index < mHeight * mWidth)
			{
				if (map[index] == 1)
					mlx_put_pixel(minimap, x, y, 0xFF0000FF); // Wall
				else
					mlx_put_pixel(minimap, x, y, 0xFFFFAAFF); // Empty
			}
			y++;
		}
		x++;
	}
	return (minimap);
}
