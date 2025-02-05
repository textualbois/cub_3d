/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:47:57 by admin             #+#    #+#             */
/*   Updated: 2025/02/05 00:45:15 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_lines_from(char **lines, int start)
{
	int	i;

	if (!lines)
		return ;
	i = start;
	while (lines[i])
	{
		free(lines[i]);
		lines[i] = NULL;
		i++;
	}
	free(lines);
	lines = NULL;
}

void free_map(t_map *map)
{
	if (!map || !map->grid)
		return;

	free_lines_from(map->grid, 0);
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
}

void	free_player(t_character *player)
{
	if (!player)
		return ;
	player->pos.x = 0;
	player->pos.y = 0;
	player->angle = 0;
}

void free_textures(t_config *config)
{
	if (!config)
		return;
	if (config->no_texture)
	{
		free(config->no_texture);
		config->no_texture = NULL;
	}
	if (config->so_texture)
	{
		free(config->so_texture);
		config->so_texture = NULL;
	}
	if (config->we_texture)
	{
		free(config->we_texture);
		config->we_texture = NULL;
	}
	if (config->ea_texture)
	{
		free(config->ea_texture);
		config->ea_texture = NULL;
	}
}

void free_config(t_config *config)
{
	if (!config)
		return;

	free_textures(config);
	free_map(&config->map);
	free_player(&config->player);
	config->floor_color[0] = 0;
	config->floor_color[1] = 0;
	config->floor_color[2] = 0;
	config->ceiling_color[0] = 0;
	config->ceiling_color[1] = 0;
	config->ceiling_color[2] = 0;
}
