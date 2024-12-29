#include "cub3d.h"

t_World_Controller *init_world(void)
{
	t_World_Controller *world;

	world = (t_World_Controller *)malloc(sizeof(t_World_Controller));
	if (!world)
		return (NULL);
	world->window = initialize_window();
	world->minimap = mlx_new_image(world->window, WIDTH, HEIGHT);
	mlx_image_to_window(world->window, world->minimap, 0, 0);
	world->player = init_mini_charachter(world->window, (t_IntPair){5, 5}, (t_IntPair){HEIGHT / 2, WIDTH / 2});
	
	if (!world->player)
	{
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


// int map[]=           //the map array. Edit to change level but keep the outer walls
// {
//  1,1,1,1,1,1,1,1,
//  1,0,1,0,0,0,0,1,
//  1,0,1,0,0,0,0,1,
//  1,0,1,0,0,0,0,1,
//  1,0,0,0,0,0,0,1,
//  1,0,0,0,0,1,0,1,
//  1,0,0,0,0,0,0,1,
//  1,1,1,1,1,1,1,1,	
// };