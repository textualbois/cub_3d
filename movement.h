/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:12:07 by isemin            #+#    #+#             */
/*   Updated: 2025/02/23 18:44:59 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVEMENT_H
# define MOVEMENT_H

# include "MLX42/MLX42.h"
# include "world.h"
# include <math.h>

void	ft_handle_input(void *param);

void	set_h_rotation(t_World_Controller *world, double angle_delta);
void	set_v_rotation(t_World_Controller *world, double angle_delta);
void	set_movement(t_World_Controller *world, t_DoublePair delta_x_y);
void	ft_cursor_input(double x_pos, double y_pos, void *param);

#endif