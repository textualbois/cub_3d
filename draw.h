/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:48:32 by isemin            #+#    #+#             */
/*   Updated: 2025/01/26 19:56:46 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "MLX42/MLX42.h"
# include "world.h"

void	ft_color_mini_character(mlx_image_t *player, int color);
void	ft_color_mini_character_direction(mlx_image_t *character, int color, t_character *player);
void	ft_color_line(mlx_image_t *img, int color, t_DoublePair start, t_DoublePair end);
void	draw_world(t_World_Controller *world);

#endif