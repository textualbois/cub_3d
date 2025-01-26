#include "cub3d.h"

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_World_Controller *world;

	int map[]=           //the map array. Edit to change level but keep the outer walls
	{
	 1,1,1,1,1,1,1,1,
	 1,0,1,0,0,0,0,1,
	 1,0,1,0,0,0,0,1,
	 1,0,1,0,0,0,0,1,
	 1,0,0,0,0,0,0,1,
	 1,0,0,0,0,1,0,1,
	 1,0,0,0,0,0,0,1,
	 1,1,1,1,1,1,1,1,	
	};

	world = init_world(map);

	init_images(world, map);

	//pre_draw(world);
	init_loops_n_hooks(world);

	return (EXIT_SUCCESS);
}