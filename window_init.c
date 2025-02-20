/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:12:13 by isemin            #+#    #+#             */
/*   Updated: 2025/02/20 13:59:48 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

mlx_t	*initialize_window(void)
{
	mlx_t	*window;

	window = mlx_init(WIDTH, HEIGHT, "Cubisimo", true);
	return (window);
}
