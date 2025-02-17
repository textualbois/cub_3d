/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:48:32 by isemin            #+#    #+#             */
/*   Updated: 2025/02/17 12:19:12 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "MLX42/MLX42.h"
# include "colors.h"
# include "extra_math.h"
# include "malloc_counter.h"
# include "ray.h"
# include "types_common.h"
# include "world.h"

typedef struct s_line_params
{
	t_DoublePair	delta;
	t_IntPair		sign;
	t_DoublePair	error;
	t_DoublePair	iter;
}					t_line_params;

void				ft_color_mini_character(mlx_image_t *player, int color);
void				ft_color_mini_character_direction(mlx_image_t *character,
						int color, t_character *player);
void				color_mini_map(mlx_image_t *map_img, t_mini_map *map);
void				ft_color_line(mlx_image_t *img, int color,
						t_DoublePair start, t_DoublePair end);
void				redraw(void *param);
void				drawray(t_character *player, mlx_image_t *map_img,
						t_mini_map *mini_map, t_DoublePair hit);
void				draw_line_between_pixels(mlx_image_t *img, t_IntPair start,
						t_IntPair end, int color);
void				highlight_line_between_pixels(mlx_image_t *img,
						t_IntPair start, t_IntPair end);
void				draw3d(mlx_image_t *world3d, t_renderData *data, int x);

#endif