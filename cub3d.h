/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:33 by isemin            #+#    #+#             */
/*   Updated: 2025/01/26 20:01:55 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "draw.h"
#include "MLX42/MLX42.h"
#include "libft/libft.h"
#include "world.h"
#include "movement.h"
#include "malloc_counter.h"

// inits //

void	init_loops_n_hooks(t_World_Controller *world);

//hooks//
// void ft_move_pc(void *param);

#endif