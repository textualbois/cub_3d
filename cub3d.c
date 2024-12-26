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

void ft_color_mini_character(mlx_image_t *player, int color)
{
	int x = 0;
	int y = 0;

	while (x < 5)
	{
		y = 0;
		while (y < 5)
		{
			mlx_put_pixel(player, x, y, color);
			y++;
		}
		x++;
	}
}

mlx_image_t* init_mini_charachter(mlx_t *window, int width, int height)
{
	mlx_image_t *player;

	player = mlx_new_image(window, width, height);
	if (!player)
		puts(mlx_strerror(mlx_errno));
	else 
		ft_color_mini_character(player, 0xFF0000FF);
	return (player);
}

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	mlx_t	*window;
	mlx_image_t* image;
	mlx_image_t* player;
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
	player = init_mini_charachter(window, 5, 5);

	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			mlx_put_pixel(image, x, y, 0xFFFFAAAA); //bleack yellow background
			y++;
		}
		x++;
	}

	mlx_image_to_window(window, image, 0, 0);
	mlx_image_to_window(window, player, WIDTH / 2, HEIGHT / 2);
	mlx_loop(window);

	return (EXIT_SUCCESS);
}