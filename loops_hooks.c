/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:56 by isemin            #+#    #+#             */
/*   Updated: 2025/02/23 00:09:19 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_exit_button(void *param)
{
	t_World_Controller	*world;

	world = (t_World_Controller *)param;
	if (mlx_is_key_down(world->window, MLX_KEY_ESCAPE))
	{
		free_world_full(world, 1);
		malloc_counter(__FILE__, __func__, __LINE__,0, RESULT, "results\n", NULL);
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
	// malloc_counter(__FILE__, __func__, __LINE__,0, RESULT, "malloc counter results\n", NULL);
	// mlx_terminate(world->window);
	// malloc_counter(__FILE__, __func__, __LINE__,0, RESULT, "malloc counter results\n", NULL);
}
