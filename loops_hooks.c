#include "cub3d.h"

void	ft_exit_button(void *param)
{
	mlx_t *window;

	window = (mlx_t *)param;
	if (mlx_is_key_down(window, MLX_KEY_ESCAPE))
		mlx_close_window(window);
}

void	init_loops_n_hooks(mlx_t *window)
{
	mlx_loop_hook(window, ft_exit_button, window);

	mlx_loop(window);
	mlx_terminate(window);
}
