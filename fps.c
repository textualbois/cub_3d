/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:41 by isemin            #+#    #+#             */
/*   Updated: 2025/01/26 17:12:41 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fps.h"

// Initializes the frame counter
t_FrameCounter	*init_frame_counter()
{
	t_FrameCounter	*frameCounter;

	frameCounter = malloc(sizeof(t_FrameCounter));
	malloc_counter(1, MALLOC, "frame counter malloc\n");
	if (frameCounter == NULL) {
		fprintf(stderr, "Failed to allocate memory for the frame counter\n");
		return(NULL);
	}
	ft_memset(frameCounter->frameCounts, 0, sizeof(frameCounter->frameCounts));
	frameCounter->intervalIndex = 0;
	frameCounter->lastUpdateTime = mlx_get_time();
	return (frameCounter);
}

// Destroys the frame counter
void	destroy_frame_counter(t_FrameCounter *frameCounter)
{
	free(frameCounter);
	malloc_counter(-1, MALLOC, "frame_counter free\n");
	frameCounter = NULL;
}

// Updates the frame counter
void update_frame_counter(t_FrameCounter *frameCounter)
{
	double currentTime;
	double deltaTime;

	currentTime = mlx_get_time();
	deltaTime = currentTime - frameCounter->lastUpdateTime;
	if (deltaTime >= 0.1)
	{
		frameCounter->intervalIndex = (frameCounter->intervalIndex + 1) % INTERVALS;
		frameCounter->frameCounts[frameCounter->intervalIndex] = 0;
		frameCounter->lastUpdateTime = currentTime;
	}
	frameCounter->frameCounts[frameCounter->intervalIndex]++;
}

// Gets the current frame count (FPS)
int	get_frame_count(t_FrameCounter *frameCounter)
{
	int	totalFrames;

	totalFrames = 0;
	for (int i = 0; i < INTERVALS; i++)
	{
		totalFrames += frameCounter->frameCounts[i];
	}
	return (totalFrames);
}
