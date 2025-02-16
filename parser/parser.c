/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:26:10 by vmamoten          #+#    #+#             */
/*   Updated: 2025/02/08 11:59:25 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "parser.h"

// int	main(int argc, char **argv)
// {
// 	t_config	*config;

// 	if (argc != 2 || !has_cub_extension(argv[1]))
// 	{
// 		printf("Usage: %s <file.cub>\n", argv[0]);
// 		return (1);
// 	}
// 	config = (t_config *)malloc(sizeof(t_config));
//	malloc_counter(1, PARSER, "uhm what malloc\n");
// 	if (!config)
// 	{
// 		perror("Memory allocation failed");
// 		return (1);
// 	}
// 	ft_bzero(config, sizeof(t_config));
// 	init_config_flags(config);
// 	if (!parse_cub_file(argv[1], config))
// 	{
// 		free_config(config);
// 		free(config);
// 		return (1);
// 	}
// 	printf("Textures:\n");
// 	printf("  NO: %s\n", config->no_texture);
// 	printf("  SO: %s\n", config->so_texture);
// 	printf("  WE: %s\n", config->we_texture);
// 	printf("  EA: %s\n", config->ea_texture);
// 	printf("Colors:\n");
// 	printf("  Floor: %d,%d,%d\n", config->floor_color[0],
// 		config->floor_color[1], config->floor_color[2]);
// 	printf("  Ceiling: %d,%d,%d\n", config->ceiling_color[0],
// 		config->ceiling_color[1], config->ceiling_color[2]);
// 	print_map(config->map.grid, config->map.width, config->map.height);
	// printf("Player position: (%.2f, %.2f), angle: %.2f radians\n",
	// 	config->player.pos.x, config->player.pos.y, config->player.angle);
// 	free_config(config);
// 	free(config);
// 	return (0);
// }
