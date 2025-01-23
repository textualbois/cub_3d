#include "world.h"

t_World_Controller *init_world(int map[])
{
	t_World_Controller *world;

	world = (t_World_Controller *)malloc(sizeof(t_World_Controller));
	if (!world)
		return (NULL);
	world->window = initialize_window();
	world->minimap = init_minimap(world->window, map);
	world->player = init_mini_charachter(world->window, (t_IntPair){5, 5}, (t_IntPair){HEIGHT / 2, WIDTH / 2});
	
	if (!world->player)
	{
		free(world);
		return (NULL);
	}
	world->frameCounter = init_frame_counter();
	if (!world->frameCounter)
	{
		free(world->player);
		free(world);
		return (NULL);
	}
	return (world);
}

mlx_t* initialize_window(void)
{
	mlx_t *window;

	printf("initing window\n");
	window = mlx_init(WIDTH, HEIGHT, "Cubisimo", true);
	if (!window)
		puts(mlx_strerror(mlx_errno));
	return (window);
}
