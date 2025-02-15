/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:25:59 by vmamoten          #+#    #+#             */
/*   Updated: 2025/02/16 00:56:18 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

// Функция возвращает 0 при успехе, или ненулевое значение при ошибке
int	init_textures(t_World_Controller *world, t_config *config)
{
	// Загрузка северной текстуры
	world->texture_no = mlx_load_png(config->no_texture);
	if (!world->texture_no)
	{
		printf("Failed to load NO texture from: %s\n", config->no_texture);
		return (1);
	}
	// Загрузка южной текстуры
	world->texture_so = mlx_load_png(config->so_texture);
	if (!world->texture_so)
	{
		printf("Failed to load SO texture from: %s\n", config->so_texture);
		return (1);
	}
	// Загрузка западной текстуры
	world->texture_we = mlx_load_png(config->we_texture);
	if (!world->texture_we)
	{
		printf("Failed to load WE texture from: %s\n", config->we_texture);
		return (1);
	}
	// Загрузка восточной текстуры
	world->texture_ea = mlx_load_png(config->ea_texture);
	if (!world->texture_ea)
	{
		printf("Failed to load EA texture from: %s\n", config->ea_texture);
		return (1);
	}
	return (0);
}
