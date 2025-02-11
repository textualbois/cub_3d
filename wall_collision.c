#include "ray.h"

static t_IntPair directions(double rayDir)
{
	t_IntPair	directions;

	if (rayDir < PI / 2 || rayDir > 3 * PI / 2)
		directions.x = 1;
	else
		directions.x = -1;
	if (rayDir < PI)
		directions.y = -1;
	else
		directions.y = 1;
	return (directions);
}

t_Collision	collision_find_wall(t_mini_map *mini_map, t_character *player, double rayDir)
{
	t_DoublePair	vertical_hit;
	t_DoublePair	horizontal_hit;
	t_IntPair		direction;

	direction = directions(rayDir);
	vertical_hit = collision_find_vertical_hit(mini_map, player, rayDir, direction);
	horizontal_hit = ray_find_horizontal_hit(mini_map, player, rayDir, direction);
	if (vertical_hit.x == -1 && horizontal_hit.x == -1)
		 return ((t_Collision){NOHIT, (t_DoublePair){-1, -1}});
	if (vertical_hit.x == -1)
		 return ((t_Collision){HORIZONTAL, horizontal_hit});
	if (horizontal_hit.x == 0)
		return ((t_Collision){VERTICAL, vertical_hit});
	if (distance(player->pos, vertical_hit) < distance(player->pos, horizontal_hit))
		return ((t_Collision){VERTICAL, vertical_hit});
	return ((t_Collision){HORIZONTAL, horizontal_hit});
}

t_DoublePair	collision_find_vertical_hit(t_mini_map *mini_map, t_character *player, double rayDir, t_IntPair direction)
{
	t_DoublePair	hit;

	if (direction.x == 1)
		hit.x = ceil_map(player->pos.x);
	else // left direction
		hit.x = floor_map(player->pos.x);

	hit.y = player->pos.y - (hit.x - player->pos.x) * tan(rayDir);

	if (is_wall(mini_map, hit, direction, VERTICAL) == false) {
			return ((t_DoublePair){-1, -1});
	}
	return (hit);
}

t_DoublePair	collision_find_horizontal_hit(t_mini_map *mini_map, t_character *player, double rayDir, t_IntPair direction)
{
	t_DoublePair	hit;

	// up direction
	if (direction.y == -1)
		hit.y = floor_map(player->pos.y);
	else // down direction
		hit.y = ceil_map(player->pos.y);
	hit.x = player->pos.x - (hit.y - player->pos.y) / tan(rayDir);
	if (is_wall(mini_map, hit, direction, HORIZONTAL) == false) {
			return ((t_DoublePair){-1, -1});
	}
	return (hit);
}
