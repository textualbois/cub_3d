#include "fps.h"

FrameCounter *frameCounter = NULL;

// Initializes the frame counter
int	init_frame_counter()
{
	frameCounter = malloc(sizeof(FrameCounter));
	if (frameCounter == NULL) {
		fprintf(stderr, "Failed to allocate memory for the frame counter\n");
		return(1);
	}
	ft_memset(frameCounter->frameCounts, 0, sizeof(frameCounter->frameCounts));
	frameCounter->intervalIndex = 0;
	frameCounter->lastUpdateTime = mlx_get_time();
	return (0);
}

// Destroys the frame counter
void	destroy_frame_counter()
{
	free(frameCounter);
	frameCounter = NULL;
}

// Updates the frame counter
void update_frame_counter()
{
	double currentTime = mlx_get_time();
	double deltaTime = currentTime - frameCounter->lastUpdateTime;

	if (deltaTime >= 0.1)
	{
		frameCounter->intervalIndex = (frameCounter->intervalIndex + 1) % INTERVALS;
		frameCounter->frameCounts[frameCounter->intervalIndex] = 0;
		frameCounter->lastUpdateTime = currentTime;
	}
	frameCounter->frameCounts[frameCounter->intervalIndex]++;
}

// Gets the current frame count (FPS)
int	get_frame_count()
{
	int totalFrames = 0;
	for (int i = 0; i < INTERVALS; i++)
	{
		totalFrames += frameCounter->frameCounts[i];
	}
	return (totalFrames);
}
