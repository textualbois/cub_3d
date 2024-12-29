#include "cub3d.h"

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_World_Controller *world;
	int x = 0;
	int y = 0;

	world = init_world();

	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			mlx_put_pixel(world->minimap, x, y, 0xFFFFAAAA); //bleack yellow minimap
			y++;
		}
		x++;
	}

	init_loops_n_hooks(world);

	return (EXIT_SUCCESS);
}