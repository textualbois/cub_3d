/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:12:04 by isemin            #+#    #+#             */
/*   Updated: 2025/02/05 23:28:26 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "movement.h"

void	ft_movement_input(void *param)
{
	t_World_Controller *world;

	world = (t_World_Controller *)param;
	if (mlx_is_key_down(world->window, MLX_KEY_E))
		set_h_rotation(world, 0.05);
	if (mlx_is_key_down(world->window, MLX_KEY_Q))
		set_h_rotation(world, -0.05);
	if (mlx_is_key_down(world->window, MLX_KEY_S))
		set_movement(world, (t_DoublePair){0.1 * cos(world->player->angle), 0.1 * sin(world->player->angle)});
	if (mlx_is_key_down(world->window, MLX_KEY_W))
		set_movement(world, (t_DoublePair){-0.1 * cos(world->player->angle), -0.1 * sin(world->player->angle)});
	if (mlx_is_key_down(world->window, MLX_KEY_A))
		set_movement(world, (t_DoublePair){0.1 * cos(world->player->angle + PI / 2), 0.1 * sin(world->player->angle + PI / 2)});
	if (mlx_is_key_down(world->window, MLX_KEY_D))
		set_movement(world, (t_DoublePair){0.1 * cos(world->player->angle - PI / 2), 0.1 * sin(world->player->angle - PI / 2)});
	printf("player pos x: %f, y: %f\n", world->player->pos.x, world->player->pos.y);
	// adjust for walls()
}

void	set_h_rotation(t_World_Controller *world, double angle_delta)
{
	write(1, "set_h_rotation\n", 15);
	world->player->angle += angle_delta;  // Decrease angle by 1 degree in radians
		write(1, "set_h_rotation2\n", 16);
	if (world->player->angle < 0)
	{
		write(1, "set_h_rotation3\n", 16);
		world->player->angle += 2 * PI;  // Wrap around if the angle goes below 0
	}
	else if (world->player->angle >= 2 * PI)
	{
		write(1, "set_h_rotation4\n", 16);
		world->player->angle -= 2 * PI;  // Wrap around if the angle exceeds 2π
	}
	write(1, "set_rotation_last\n", 16);
}

void	set_movement(t_World_Controller *world, t_DoublePair delta_x_y)
{
	write(1, "set_movement\n", 13);
	world->player->pos.x += delta_x_y.x;
	world->player->pos.y += delta_x_y.y;
}

