/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_character.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:37 by isemin            #+#    #+#             */
/*   Updated: 2025/01/26 17:12:42 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "character.h"

void ft_color_mini_character(mlx_image_t *player, int color)
{
	int x = 0;
	int y = 0;

	while (x < 5)
	{
		y = 0;
		while (y < 5)
		{
			mlx_put_pixel(player, x, y, color);
			y++;
		}
		x++;
	}
}

void ft_color_mini_character_direction(mlx_image_t *player, int color, float angle)
{
	int x, y;
	int size = 9;  // Total size of the character image
	int bodySize = 7;  // Body is centered within 7x7, so it's 5x5
	int offset = 1;  // Offset for the body to be centered
	int centerX = size / 2;
	int centerY = size / 2;
	int lineLength = 4;  // Length of the directional line, stays within the outer border

	// Color the main body of the character
	for (x = offset; x < offset + bodySize; x++) {
		for (y = offset; y < offset + bodySize; y++) {
			mlx_put_pixel(player, x, y, color);
		}
	}

	// Calculate the end point of the line from the center
	int endX = centerX + (int)(lineLength * cos(angle));
	int endY = centerY - (int)(lineLength * sin(angle));  // Subtracting because graphical y-axis is inverted

	// Draw the direction line
	// Ensure that the line stays within bounds of the image
	endX = endX < 0 ? 0 : (endX >= size ? size - 1 : endX);
	endY = endY < 0 ? 0 : (endY >= size ? size - 1 : endY);

	// Bresenham's line algorithm for better line drawing
	int dx = abs(endX - centerX), sx = centerX < endX ? 1 : -1;
	int dy = -abs(endY - centerY), sy = centerY < endY ? 1 : -1;
	int err = dx + dy, e2;  // Error value e_xy

	for (;;) {  // The loop will break when the line is completely drawn
		mlx_put_pixel(player, centerX, centerY, 0xFFFFFFFF);  // Draw in white for visibility
		if (centerX == endX && centerY == endY) break;
		e2 = 2 * err;
		if (e2 >= dy) { err += dy; centerX += sx; }
		if (e2 <= dx) { err += dx; centerY += sy; }
	}
}
