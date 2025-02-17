/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:33 by isemin            #+#    #+#             */
/*   Updated: 2025/02/17 12:09:46 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "draw.h"
# include "libft/libft.h"
# include "malloc_counter.h"
# include "movement.h"
# include "world.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

void	init_loops_n_hooks(t_World_Controller *world);

#endif