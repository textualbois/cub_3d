/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:20 by isemin            #+#    #+#             */
/*   Updated: 2025/02/17 12:07:43 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser/parser.h"

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

int	main(int argc, char **argv)
{
	t_config			*config;
	t_World_Controller	*world;

	if (argc != 2 || !has_cub_extension(argv[1]))
		return (printf("Usage: %s <file.cub>\n", argv[0]), 1);
	config = (t_config *)malloc(sizeof(t_config));
	malloc_counter(1, MALLOC, "main config malloc\n");
	if (!config)
		return (1);
	ft_bzero(config, sizeof(t_config));
	init_config_flags(config);
	if (!parse_cub_file(argv[1], config))
	{
		free_config(config);
		free(config);
		malloc_counter(-1, MALLOC, "config main free\n");
		return (1);
	}
	world = init_world(config);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	draw_world(world);
	init_loops_n_hooks(world);
	free_config(config);
	free(config);
	malloc_counter(-1, MALLOC, "config main free\n");
	return (EXIT_SUCCESS);
}
