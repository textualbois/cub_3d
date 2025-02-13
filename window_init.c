/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:12:13 by isemin            #+#    #+#             */
/*   Updated: 2025/02/13 13:51:50 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

mlx_t* initialize_window(void)
{
	mlx_t *window;

	//ft_putstr("Initializing window\n");
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	window = mlx_init(WIDTH, HEIGHT, "Cubisimo", true);
	//if (!window)
		//puts(mlx_strerror(mlx_errno));
	return (window);
}
