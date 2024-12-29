#include "cub3d.h"

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

t_character* init_mini_charachter(mlx_t *window, t_IntPair size, t_IntPair pos)
{
	t_character *player;

	player = (t_character *)malloc(sizeof(t_character));
	if (!player)
		puts(mlx_strerror(mlx_errno));
	else
	{
		player->size = size;
		player->pos = pos;
		player->angle = 0;
		player->image = mlx_new_image(window, size.x, size.y);
		ft_color_mini_character(player->image, 0xFF0000FF);
	}
	return (player);
}
