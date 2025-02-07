/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:52:42 by admin             #+#    #+#             */
/*   Updated: 2025/02/07 19:54:07 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_valid_cell(t_map *map, int i, int j)
{
	char	up;
	char	down;
	char	left;
	char	right;

	up = ' ';
	down = ' ';
	left = ' ';
	right = ' ';
	if (i > 0)
		up = map->grid[i - 1][j];
	if (i < map->height - 1)
		down = map->grid[i + 1][j];
	if (j > 0)
		left = map->grid[i][j - 1];
	if (j < map->width - 1)
		right = map->grid[i][j + 1];
	if (i == 0 || i == map->height - 1 || j == 0 || j == map->width - 1)
		return (0);
	if (up == ' ' || down == ' ' || left == ' ' || right == ' ')
		return (0);
	return (1);
}

int	is_sur_by_wals(t_map *map, int i, int j)
{
	char	up;
	char	down;
	char	left;
	char	right;

	up = '1';
	down = '1';
	left = '1';
	right = '1';
	if (i > 0)
		up = map->grid[i - 1][j];
	if (i < map->height - 1)
		down = map->grid[i + 1][j];
	if (j > 0)
		left = map->grid[i][j - 1];
	if (j < map->width - 1)
		right = map->grid[i][j + 1];
	if ((up != '1' && up != ' ') || (down != '1' && down != ' '))
		return (0);
	if ((left != '1' && left != ' ') || (right != '1' && right != ' '))
		return (0);
	return (1);
}

int	is_valid_map_char(char c)
{
	if (c == ' ' || c == '1' || c == '0' || c == 'N' || c == 'E' || c == 'W'
		|| c == 'S')
		return (1);
	return (0);
}

double	get_angle_from_char(char dir)
{
	if (dir == 'N')
		return (3 * M_PI_2);
	if (dir == 'S')
		return (M_PI_2);
	if (dir == 'E')
		return (0);
	if (dir == 'W')
		return (M_PI);
	return (0);
}

void	set_player_position(t_config *config, int x, int y, char dir)
{
	config->player.pos.x = (double)x + 0.5;
	config->player.pos.y = (double)y + 0.5;
	config->player.angle = get_angle_from_char(dir);
}
