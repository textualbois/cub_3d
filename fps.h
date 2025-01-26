/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:44 by isemin            #+#    #+#             */
/*   Updated: 2025/01/26 17:12:37 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FPS_H
# define FPS_H

#include <stdio.h>
#include "MLX42/MLX42.h"
#include "libft/libft.h"
#include <math.h>
#include <stdlib.h>

#define INTERVALS 10

typedef struct s_FrameCounter {
	int frameCounts[INTERVALS];
	int intervalIndex;
	double lastUpdateTime;
}	t_FrameCounter;

t_FrameCounter	*init_frame_counter();
void			destroy_frame_counter(t_FrameCounter *frameCounter);
void			update_frame_counter(t_FrameCounter *frameCounter);
double			get_frame_count(t_FrameCounter *frameCounter);

#endif