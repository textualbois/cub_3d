/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_common.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 19:49:07 by isemin            #+#    #+#             */
/*   Updated: 2025/02/16 02:06:16 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_COMMON_H
# define TYPES_COMMON_H

# include "types_numeric.h"
# include "MLX42/MLX42.h"

typedef struct s_character
{
	t_IntPair size;
	t_DoublePair pos;
	t_DoublePair angle;
}	t_character;

typedef struct	s_mini_map
{
	int				**map;
	t_IntPair		size_int;		// map grid dimensions
	t_IntPair		size;			// size of the world // { size_int.x * TILE_SIZE, size_int.y * TILE_SIZE }
	t_IntPair		view_port;		// left and bottom-most corner of visible zone
	t_IntPair		visible_size;	// VISIBLE_TILES * TILE_SIZE
	int				ppu; 			// pixels per unit of size. for example we have 8 tiles,
									// each tile is 10 units of land, where each unit is 10 pixels
}	t_mini_map;

typedef struct s_renderData {
	t_DoublePair	hit;
	int				x;
	int				wall_type;
	int				txtr_code;
	double			t2t_ratio;
	double			rayDir;
	t_DoublePair	playerDir;
	t_DoublePair	playerPos;
	int				txtr_start;
	int				txtr_end;
	t_DoublePair	txtr;
	mlx_texture_t	*texture;
	t_IntPair		pixel;
}	t_renderData;

typedef struct s_FrameCounter {
	int			frameCounts[INTERVALS];
	int			intervalIndex;
	double		lastUpdateTime;
	mlx_image_t	*first_digit;
	mlx_image_t	*second_digit;
	mlx_image_t	*third_digit;
}	t_FrameCounter;

typedef struct s_World_Controller
{
	mlx_t			*window;
	t_IntPair		size;
	t_character		*player;
	t_mini_map		*mini_map;

	mlx_image_t		*map_img;
	mlx_image_t		*miniCharacter;
	mlx_image_t		*world3d;
	mlx_texture_t	*texture_no;
	mlx_texture_t	*texture_so;
	mlx_texture_t	*texture_we;
	mlx_texture_t	*texture_ea;
	t_FrameCounter	*frameCounter;
}					t_World_Controller;

#endif