/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:12:07 by isemin            #+#    #+#             */
/*   Updated: 2025/02/01 18:07:38 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVEMENT_H
# define MOVEMENT_H

#include "world.h"
#include <math.h>
#include "MLX42/MLX42.h"

void ft_movement_input(void *param);
//void set_v_rotation(t_World_Controller *world, int angle_delta);
void set_h_rotation(t_World_Controller *world, double angle_delta);
void set_movement(t_World_Controller *world, t_DoublePair delta_x_y);
// void get

#endif