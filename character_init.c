#include "character.h"

t_character* init_mini_character(mlx_t *window, t_IntPair size, t_IntPair pos)
{
	t_character *player;

	player = (t_character *)malloc(sizeof(t_character));
	// if (!player)
	// 	 ;//error msg ?? (mlx_strerror(mlx_errno));
	if (player)
	{
		player->size = size;
		player->angle = 90;
		// player->image = mlx_new_image(window, size.x, size.y);
		// ft_color_mini_character_direction(player->image, 0xFF0000FF, player->angle);
		// mlx_image_to_window(window, player->image, pos.x, pos.y);
		// player->pos.x = &player->image->instances[0].x;
		// player->pos.y = &player->image->instances[0].y;
	}
	return (player);
}
