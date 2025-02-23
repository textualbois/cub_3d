/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:20 by isemin            #+#    #+#             */
/*   Updated: 2025/02/23 18:52:03 by vmamoten         ###   ########.fr       */
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
		return (printf("Usage: %s <file.cub>\n", argv[0]), EXIT_FAILURE);
	config = (t_config *)malloc(sizeof(t_config));
	if (!config)
		return (EXIT_FAILURE);
	ft_bzero(config, sizeof(t_config));
	init_config_flags(config);
	if (!parse_cub_file(argv[1], config))
		return (free_free_config(config), EXIT_FAILURE);
	world = init_world(config);
	if (world != NULL)
	{
		mlx_set_setting(MLX_STRETCH_IMAGE, true);
		draw_world(world);
		init_loops_n_hooks(world);
		free_world_full(world, 0);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
