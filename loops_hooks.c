/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:56 by isemin            #+#    #+#             */
/*   Updated: 2025/02/20 13:50:23 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_exit_button(void *param)
{
	t_World_Controller	*world;

	world = (t_World_Controller *)param;
	if (mlx_is_key_down(world->window, MLX_KEY_ESCAPE))
	{
		if (world->map_img)
		{
			mlx_delete_image(world->window, world->map_img);
			world->map_img = NULL;
		}
		if (world->mini_character)
		{
			mlx_delete_image(world->window, world->mini_character);
			world->mini_character = NULL;
		}
		free(world->player);
		malloc_counter(-1, MALLOC, "world->player free\n");
		world->player = NULL;
		mlx_close_window(world->window);
		free(world);
		malloc_counter(-1, MALLOC, "world free\n");
		world = NULL;
		malloc_counter(0, RESULT, "malloc counter results\n");
		exit(EXIT_SUCCESS);
	}
}

void	init_loops_n_hooks(t_World_Controller *world)
{
	mlx_loop_hook(world->window, ft_exit_button, world);
	mlx_loop_hook(world->window, ft_handle_input, world);
	mlx_loop_hook(world->window, redraw, world);
	mlx_cursor_hook(world->window, ft_cursor_input, world);
	mlx_loop(world->window);
	malloc_counter(0, RESULT, "malloc counter results\n");
	mlx_terminate(world->window);
	malloc_counter(0, RESULT, "malloc counter results\n");
}
