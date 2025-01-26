/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:53 by isemin            #+#    #+#             */
/*   Updated: 2025/01/26 17:12:31 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

t_World_Controller *init_world(int map[])
{
	t_World_Controller *world;

	world = (t_World_Controller *)malloc(sizeof(t_World_Controller));
	if (!world)
		return (NULL);
	world->window = initialize_window();
	if (!world->window)
	{
		free(world);
		return (NULL);
	}
	world->player = init_mini_character((t_IntPair){5, 5}, (t_IntPair){HEIGHT / 2, WIDTH / 2});
	if (!world->player)
	{
		free(world);
		return (NULL);
	}

	if (init_images(world, map) != 0)
	{
		free(world->player);
		free(world);
		return (NULL);
	}


	// world->frameCounter = init_frame_counter();
	// if (!world->frameCounter)
	// {
	// 	free(world->player);
	// 	free(world);
	// 	return (NULL);
	// }
	return (world);
}

