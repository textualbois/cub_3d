/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:44 by isemin            #+#    #+#             */
/*   Updated: 2025/02/16 02:36:26 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FPS_H
# define FPS_H

#include <stdio.h>
#include "MLX42/MLX42.h"
#include "libft/libft.h"
#include <math.h>
#include <stdlib.h>
#include "types_common.h"

t_FrameCounter	*init_frame_counter(mlx_t *mlx);
void			draw_frames(t_FrameCounter *frameCounter);
// mlx_image_t		*init_text_box(mlx_t *window);
void			destroy_frame_counter(mlx_t *mlx, t_FrameCounter *frameCounte);
void			update_frame_counter(t_FrameCounter *frameCounter);
int			get_frame_count(t_FrameCounter *frameCounter);

#endif