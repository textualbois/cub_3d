/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:56 by isemin            #+#    #+#             */
/*   Updated: 2025/01/26 17:12:27 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_exit_button(void *param)
{
	t_World_Controller	*world;

	world = (t_World_Controller *)param;
	if (mlx_is_key_down(world->window, MLX_KEY_ESCAPE))
	{
		if (world->minimap)
		{
			mlx_delete_image(world->window, world->minimap);
			world->minimap = NULL;
		}
		if (world->miniCharacter)
		{
			mlx_delete_image(world->window, world->miniCharacter);
			world->miniCharacter = NULL;
		}
		free(world->player);
		world->player = NULL;
		mlx_close_window(world->window);
		free(world);
		world = NULL;
		exit(EXIT_SUCCESS);
	}
}

void	init_loops_n_hooks(t_World_Controller *world)
{
	mlx_loop_hook(world->window, ft_exit_button, world);
	mlx_loop_hook(world->window, ft_movement_input, world);
	mlx_loop(world->window);
	mlx_terminate(world->window);
	// draw_world(world);
}
