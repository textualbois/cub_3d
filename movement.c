/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:12:04 by isemin            #+#    #+#             */
/*   Updated: 2025/02/23 20:07:47 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "movement.h"

static void	ft_rotation_input(t_World_Controller *world)
{
	if (mlx_is_key_down(world->window, MLX_KEY_E)
		|| mlx_is_key_down(world->window, MLX_KEY_RIGHT))
		set_h_rotation(world, -0.05);
	if (mlx_is_key_down(world->window, MLX_KEY_Q)
		|| mlx_is_key_down(world->window, MLX_KEY_LEFT))
		set_h_rotation(world, +0.05);
	if (mlx_is_key_down(world->window, MLX_KEY_UP))
		set_v_rotation(world, 0.05);
	if (mlx_is_key_down(world->window, MLX_KEY_DOWN))
		set_v_rotation(world, -0.05);
}

void	ft_movement_input(void *param)
{
	t_World_Controller	*world;

	world = (t_World_Controller *)param;
	if (mlx_is_key_down(world->window, MLX_KEY_D))
		set_movement(world, (t_DoublePair){sin(world->player->angle.x),
			cos(world->player->angle.x)});
	if (mlx_is_key_down(world->window, MLX_KEY_A))
		set_movement(world, (t_DoublePair){-sin(world->player->angle.x),
			-cos(world->player->angle.x)});
	if (mlx_is_key_down(world->window, MLX_KEY_W))
		set_movement(world, (t_DoublePair){sin(world->player->angle.x + PI / 2),
			cos(world->player->angle.x + PI / 2)});
	if (mlx_is_key_down(world->window, MLX_KEY_S))
		set_movement(world, (t_DoublePair){sin(world->player->angle.x - PI / 2),
			cos(world->player->angle.x - PI / 2)});
}

void	ft_handle_input(void *param)
{
	t_World_Controller	*world;

	world = (t_World_Controller *)param;
	ft_rotation_input(world);
	ft_movement_input(world);
}

void	set_movement(t_World_Controller *world, t_DoublePair delta)
{
	double	new_x;
	double	new_y;

	new_x = world->player->pos.x + delta.x;
	new_y = world->player->pos.y;
	if (!hitbox_collision(world, new_x, new_y))
		world->player->pos.x = new_x;
	new_x = world->player->pos.x;
	new_y = world->player->pos.y + delta.y;
	if (!hitbox_collision(world, new_x, new_y))
	{
		world->player->pos.y = new_y;
	}
}
