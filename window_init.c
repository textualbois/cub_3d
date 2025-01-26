/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:12:13 by isemin            #+#    #+#             */
/*   Updated: 2025/01/26 17:12:22 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
