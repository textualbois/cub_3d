/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:20 by isemin            #+#    #+#             */
/*   Updated: 2025/02/08 01:15:15 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser/parser.h"

void	print_map(char **map_grid, int map_width, int map_height)
{
	int	i;

	i = 0;
	printf("Map (%d x %d):\n", map_width, map_height);
	while (i < map_height)
	{
		printf("%s\n", map_grid[i]);
		i++;
	}
}

int	has_cub_extension(const char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (0);
	if (len > 4 && filename[len - 5] == '.')
		return (0);
	return (1);
}

void	init_config_flags(t_config *config)
{
	if (!config)
		return ;
	config->has_no = 0;
	config->has_so = 0;
	config->has_we = 0;
	config->has_ea = 0;
	config->has_floor = 0;
	config->has_ceiling = 0;
}

int main(int argc, char **argv)
{
	t_config	*config;

	if (argc != 2 || !has_cub_extension(argv[1]))
	{
		printf("Usage: %s <file.cub>\n", argv[0]);
		return (1);
	}
	config = (t_config *)malloc(sizeof(t_config));
	if (!config)
	{
		perror("Memory allocation failed");
		return (1);
	}
	ft_bzero(config, sizeof(t_config));
	init_config_flags(config);
	if (!parse_cub_file(argv[1], config))
	{
		free_config(config);
		free(config);
		return (1);
	}
	print_map(config->map.grid, config->map.width, config->map.height);
	
	t_World_Controller *world;

	// int map[8][8]=
	// {
	// 	{1,1,1,1,1,1,1,1},
	// 	{1,0,1,0,0,0,0,1},
	// 	{1,0,1,0,0,0,0,1},
	// 	{1,0,1,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,1,0,1},
	// 	{1,0,0,0,0,0,0,1},
	// 	{1,1,1,1,1,1,1,1},
	// };

	ft_putstr_fd("Hello, World!\n", 1);
	world = init_world(config);
	ft_putstr_fd("Hello, Images!\n", 1);
	// init_images(world);//, map);
	ft_putstr_fd("Hello, Draw!\n", 1);
	draw_world(world);
	ft_putstr_fd("Hello, Loops and Hooks!\n", 1);
	init_loops_n_hooks(world);
	ft_putstr_fd("Bye all!\n", 1);
	free_config(config);
	free(config);
	return (EXIT_SUCCESS);
}