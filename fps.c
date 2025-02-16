/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:41 by isemin            #+#    #+#             */
/*   Updated: 2025/02/16 02:38:30 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fps.h"

void draw_frames(t_FrameCounter *frameCounter)
{
	int	frameCount;
	int	first_digit;
	int	second_digit;
	int	third_digit;

	frameCount = get_frame_count(frameCounter);
	if (frameCount > 999)
		frameCount = 999;
	first_digit = frameCount / 100;
	second_digit = (frameCount / 10) % 10;
	third_digit = frameCount % 10;
	frameCounter->first_digit->instances[0].x = first_digit * frameCounter->first_digit->width / 10;
	frameCounter->second_digit->instances[0].x = second_digit * frameCounter->second_digit->width / 10;
	frameCounter->third_digit->instances[0].x = third_digit * frameCounter->third_digit->width / 10;
}

static int init_frame_counter_images(t_FrameCounter *frameCounter, mlx_t *mlx)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("textures/numbers_36_360.png");
	if (texture == NULL)
	{
		printf("Failed to load the first digit texture\n");
		return (1);
	}
	frameCounter->first_digit = mlx_texture_to_image(mlx, texture);
	frameCounter->second_digit = mlx_texture_to_image(mlx, texture);
	frameCounter->third_digit = mlx_texture_to_image(mlx, texture);
	mlx_image_to_window(mlx, frameCounter->first_digit, 0, 0);
	mlx_image_to_window(mlx, frameCounter->second_digit, frameCounter->first_digit->width * 1.1, 0);
	mlx_image_to_window(mlx, frameCounter->third_digit, frameCounter->second_digit->width * 1.1, 0);
	mlx_delete_texture(texture);
	return (0);
}

// Initializes the frame counter
t_FrameCounter	*init_frame_counter(mlx_t *mlx)
{
	t_FrameCounter	*frameCounter;

	frameCounter = malloc(sizeof(t_FrameCounter));
	if (frameCounter == NULL) {
		fprintf(stderr, "Failed to allocate memory for the frame counter\n");
		return(NULL);
	}
	init_frame_counter_images(frameCounter, mlx);
	ft_memset(frameCounter->frameCounts, 0, sizeof(frameCounter->frameCounts));
	frameCounter->intervalIndex = 0;
	frameCounter->lastUpdateTime = mlx_get_time();
	return (frameCounter);
}

// Destroys the frame counter
void	destroy_frame_counter(mlx_t *mlx, t_FrameCounter *frameCounter)
{
	mlx_delete_image(mlx, frameCounter->first_digit);
	mlx_delete_image(mlx, frameCounter->second_digit);
	mlx_delete_image(mlx, frameCounter->third_digit);
	free(frameCounter);
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
