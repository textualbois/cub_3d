/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:44 by isemin            #+#    #+#             */
/*   Updated: 2025/02/23 18:44:59 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FPS_H
# define FPS_H

# include "MLX42/MLX42.h"
# include "libft/libft.h"
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