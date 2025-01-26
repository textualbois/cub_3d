/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:20 by isemin            #+#    #+#             */
/*   Updated: 2025/01/26 17:14:43 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	// ft_putstr_fd("Hello, World!\n", 1);
	world = init_world(map);
	// ft_putstr_fd("Hello, Images!\n", 1);
	init_images(world, map);
	//pre_draw(world);
	// ft_putstr_fd("Hello, Loops and Hooks!\n", 1);
	init_loops_n_hooks(world);
	// ft_putstr_fd("Bye all!\n", 1);

	return (EXIT_SUCCESS);
}