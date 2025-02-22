/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:41 by isemin            #+#    #+#             */
/*   Updated: 2025/02/22 21:28:37 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fps.h"

t_frame_counter	*init_frame_counter(void)
{
	t_frame_counter	*fr_counter;

	fr_counter = malloc(sizeof(t_frame_counter));
	malloc_counter(__FILE__, __func__, __LINE__,1, MALLOC, "frame counter malloc\n", fr_counter);
	if (fr_counter == NULL)
	{
		fprintf(stderr, "Failed to allocate memory for the frame counter\n");
		return (NULL);
	}
	ft_memset(fr_counter->frame_counts, 0, sizeof(fr_counter->frame_counts));
	fr_counter->interval_index = 0;
	fr_counter->last_update_time = mlx_get_time();
	return (fr_counter);
}

void	destroy_frame_counter(t_frame_counter *fr_counter)
{
	malloc_counter(__FILE__, __func__, __LINE__,-1, MALLOC, "frame_counter free\n", fr_counter);
	free(fr_counter);
	fr_counter = NULL;
}

void	update_frame_counter(t_frame_counter *fr_counter)
{
	double	current_time;
	double	delta_time;

	current_time = mlx_get_time();
	delta_time = current_time - fr_counter->last_update_time;
	if (delta_time >= 0.1)
	{
		fr_counter->interval_index = (fr_counter->interval_index + 1)
			% INTERVALS;
		fr_counter->frame_counts[fr_counter->interval_index] = 0;
		fr_counter->last_update_time = current_time;
	}
	fr_counter->frame_counts[fr_counter->interval_index]++;
}

int	get_frame_count(t_frame_counter *fr_counter)
{
	int	total_frames;
	int	i;

	total_frames = 0;
	i = 0;
	while (i < INTERVALS)
	{
		total_frames += fr_counter->frame_counts[i];
		i++;
	}
	return (total_frames);
}
