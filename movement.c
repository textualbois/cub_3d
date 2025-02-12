/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:12:04 by isemin            #+#    #+#             */
/*   Updated: 2025/02/12 21:54:46 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #define PLAYER_COLLISION_HALF_WIDTH (5.0 / 2.0)
// #define PLAYER_COLLISION_HALF_HEIGHT (5.0 / 2.0)

#include "movement.h"

static int	hitbox_collision(t_World_Controller *world, double center_x,
		double center_y)
{
	double	half_w;
	double	half_h;
	double	corners[4][2];
	int		tile_x;
	int		tile_y;
	int		i;

	half_w = 0;
	half_h = 0;
	// Расчёт координат четырёх углов хитбокса (если pos — центр)
	// Верхний левый угол
	corners[0][0] = center_x - half_w - 2;
	corners[0][1] = center_y - half_h - 2;
	// Верхний правый угол
	corners[1][0] = center_x + half_w;
	corners[1][1] = center_y - half_h;
	// Нижний левый угол
	corners[2][0] = center_x - half_w - 2;
	corners[2][1] = center_y + half_h;
	// Нижний правый угол
	corners[3][0] = center_x + half_w;
	corners[3][1] = center_y + half_h;
	i = 0;
	while (i < 4)
	{
		tile_x = (int)(corners[i][0] / TILE_SIZE);
		tile_y = (int)(corners[i][1] / TILE_SIZE);
		// Проверка выхода за пределы карты
		if (tile_x < 0 || tile_y < 0 || tile_x >= world->mini_map->size_int.x
			|| tile_y >= world->mini_map->size_int.y)
			return (1);
		// Проверка на стену (ячейка содержит '1')
		if (world->mini_map->map[tile_y][tile_x] == '1')
			return (1);
		i++;
	}
	return (0);
}

/*
 * Функция ft_movement_input обрабатывает нажатия клавиш и инициирует
 * перемещения и повороты игрока.
 */
void	ft_movement_input(void *param)
{
	t_World_Controller	*world;

	world = (t_World_Controller *)param;
	// Поворот игрока
	if (mlx_is_key_down(world->window, MLX_KEY_E) || mlx_is_key_down(world->window, MLX_KEY_RIGHT))
		set_h_rotation(world, -0.05);
	if (mlx_is_key_down(world->window, MLX_KEY_Q) || mlx_is_key_down(world->window, MLX_KEY_LEFT))
		set_h_rotation(world, +0.05);
	if (mlx_is_key_down(world->window, MLX_KEY_UP))
		set_v_rotation(world, 0.05);
	if (mlx_is_key_down(world->window, MLX_KEY_DOWN))
		set_v_rotation(world, -0.05);
	if (mlx_is_key_down(world->window, MLX_KEY_D))
		set_movement(world, (t_DoublePair){1 * sin(world->player->angle.y), 1 * cos(world->player->angle.y)});
	if (mlx_is_key_down(world->window, MLX_KEY_A))
		set_movement(world, (t_DoublePair){-1 * sin(world->player->angle.y), -1 * cos(world->player->angle.y)});
	if (mlx_is_key_down(world->window, MLX_KEY_W))
		set_movement(world, (t_DoublePair){1 * sin(world->player->angle.y + PI / 2), 1 * cos(world->player->angle.y + PI / 2)});
	if (mlx_is_key_down(world->window, MLX_KEY_S))
		set_movement(world, (t_DoublePair){1 * sin(world->player->angle.y - PI / 2), 1 * cos(world->player->angle.y - PI / 2)});
	printf("player pos x: %f, y: %f\n", world->player->pos.x,
		world->player->pos.y);
	// Остальные обновления (например, рендер и т.п.)

		world = (t_World_Controller *)param;

}

/*
 * Функция set_h_rotation изменяет угол обзора игрока.
 */
void	set_h_rotation(t_World_Controller *world, double angle_delta)
{
	write(1, "set_h_rotation\n", 15);
	world->player->angle.y += angle_delta;
	write(1, "set_h_rotation2\n", 16);
	if (world->player->angle.y < 0)
	{
		write(1, "set_h_rotation3\n", 16);
		world->player->angle.y += 2 * PI;
	}
	else if (world->player->angle.y >= 2 * PI)
	{
		write(1, "set_h_rotation4\n", 16);
		world->player->angle.y -= 2 * PI;
	}
	write(1, "set_rotation_last\n", 16);
}

/*
 * Функция set_v_rotation изменяет угол обзора игрока по вертикали.
 */
void	set_v_rotation(t_World_Controller *world, double angle_delta)
{
	write(1, "set_v_rotation\n", 15);
	world->player->angle.x += angle_delta;
	if (world->player->angle.x < -PI / 2)
		world->player->angle.x = -PI / 2;
	if (world->player->angle.x > PI / 2)
		world->player->angle.x = PI / 2;
}

/*
 * Функция set_movement перемещает игрока с проверкой столкновений для его
 * хитбокса. Перемещение выполняется по осям отдельно: сначала по X, затем по Y.
 */
void	set_movement(t_World_Controller *world, t_DoublePair delta)
{
	double	new_x;
	double	new_y;

	write(1, "set_movement\n", 13);
	// Проверка перемещения по оси X
	new_x = world->player->pos.x + delta.x;
	new_y = world->player->pos.y; // Y остаётся прежним
	if (!hitbox_collision(world, new_x, new_y))
	{
		world->player->pos.x = new_x;
	}
	// Проверка перемещения по оси Y
	new_x = world->player->pos.x; // Используем уже обновлённый X
	new_y = world->player->pos.y + delta.y;
	if (!hitbox_collision(world, new_x, new_y))
	{
		world->player->pos.y = new_y;
	}
}
