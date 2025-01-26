#include "window.h"

mlx_t* initialize_window(void)
{
	mlx_t *window;

	//ft_putstr("Initializing window\n");
	window = mlx_init(WIDTH, HEIGHT, "Cubisimo", true);
	//if (!window)
		//puts(mlx_strerror(mlx_errno));
	return (window);
}
