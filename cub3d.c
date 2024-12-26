#include "cub3d.h"

static mlx_t* initialize_window(void)
{
	mlx_t *window;

	printf("initing window\n");
	window = mlx_init(WIDTH, HEIGHT, "Cubisimo", true);
	if (!window)
		puts(mlx_strerror(mlx_errno));
	return (window);
}

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	mlx_t	*window;
	mlx_image_t* image;
	int x = 0;
	int y = 0;

	window = initialize_window();
	if (!window)
	{
		printf("no window\n");
		return (EXIT_FAILURE); // Error message printed in `initialize_window`.
	}
	printf("got window\n");

	image = mlx_new_image(window, WIDTH, HEIGHT);

	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			mlx_put_pixel(image, x, y, 0xFFAAAAAA); //peachbackground
			y++;
		}
		x++;
	}

	mlx_image_to_window(window, image, 0, 0);
	mlx_loop(window);

	return (EXIT_SUCCESS);
}