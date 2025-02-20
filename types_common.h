/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_common.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:49:07 by isemin            #+#    #+#             */
/*   Updated: 2025/02/20 16:09:20 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_COMMON_H
# define TYPES_COMMON_H

# include "MLX42/MLX42.h"
# include "malloc_counter.h"
# include "types_numeric.h"

typedef struct s_character
{
	t_IntPair		size;
	t_DoublePair	pos;
	t_DoublePair	angle;
}					t_character;

typedef struct s_mini_map
{
	int				**map;
	t_IntPair		size_int;
	t_IntPair		size;
	t_IntPair		view_port;
	t_IntPair		visible_size;
	int				ppu;

}					t_mini_map;

typedef struct s_renderData
{
	t_DoublePair	hit;
	int				x;
	int				wall_type;
	int				txtr_code;
	double			t2t_ratio;
	double			ray_dir;
	t_DoublePair	player_dir;
	t_DoublePair	player_pos;
	int				txtr_start;
	int				txtr_end;
	t_DoublePair	txtr;
	mlx_texture_t	*texture;
	t_IntPair		pixel;
}					t_renderData;

typedef struct s_World_Controller
{
	mlx_t			*window;
	t_IntPair		size;
	t_character		*player;
	t_mini_map		*mini_map;

	mlx_image_t		*map_img;
	mlx_image_t		*mini_character;
	mlx_image_t		*world3d;

	mlx_texture_t	*texture_no;
	mlx_texture_t	*texture_so;
	mlx_texture_t	*texture_we;
	mlx_texture_t	*texture_ea;

	int				floor_color[3];
	int				ceiling_color[3];

}					t_World_Controller;

#endif