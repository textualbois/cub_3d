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
			mlx_put_pixel(world->background, x, y, 0xFFFFAAAA); //bleack yellow background
			y++;
		}
		x++;
	}

	mlx_image_to_window(world->window, world->background, 0, 0);
	mlx_image_to_window(world->window, world->player->image, WIDTH / 2, HEIGHT / 2);
	init_loops_n_hooks(world);

	return (EXIT_SUCCESS);
}