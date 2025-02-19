/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:44 by isemin            #+#    #+#             */
/*   Updated: 2025/02/19 17:35:51 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FPS_H
# define FPS_H

# include "MLX42/MLX42.h"
# include "libft/libft.h"
# include "malloc_counter.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define INTERVALS 10

typedef struct s_frame_counter
{
	int			frame_counts[INTERVALS];
	int			interval_index;
	double		last_update_time;

}				t_frame_counter;

t_frame_counter	*init_frame_counter(void);

void			destroy_frame_counter(t_frame_counter *frame_counter);
void			update_frame_counter(t_frame_counter *frame_counter);
double			get_frame_count(t_frame_counter *frame_counter);

#endif