#include "cub3d.h"

void	ft_exit_button(void *param)
{
	t_World_Controller *world;

	world = (t_World_Controller *)param;
	if (mlx_is_key_down(world->window, MLX_KEY_ESCAPE))
		mlx_close_window(world->window);
}

void	init_loops_n_hooks(t_World_Controller *world)
{

	mlx_loop_hook(world->window, ft_exit_button, world);
	mlx_loop_hook(world->window, ft_move_pc, world);

	mlx_loop(world->window);
	mlx_terminate(world->window);
}
