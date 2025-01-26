#include "character.h"

t_character* init_mini_character(t_IntPair size, t_IntPair pos)
{
	t_character *player;

	player = (t_character *)malloc(sizeof(t_character));
	if (player)
	{
		player->size = size;
		player->angle = 90;
		player->pos.x = (double)pos.x;
		player->pos.y = (double)pos.y;
	}
	return (player);
}
