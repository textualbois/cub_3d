/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:12:18 by isemin            #+#    #+#             */
/*   Updated: 2025/02/13 14:35:02 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "./parser/parser.h"
# include "MLX42/MLX42.h"
# include "character.h"
# include "draw.h"
# include "fps.h"
# include "mini_map.h"
# include "window.h"

typedef struct s_World_Controller
{
	mlx_t			*window;
	t_IntPair		size;
	t_character		*player;
	t_mini_map *mini_map;

	mlx_image_t		*map_img;
	mlx_image_t		*miniCharacter;
	mlx_image_t		*world3d;
	mlx_image_t		*texture_no;
	mlx_image_t		*texture_so;
	mlx_image_t		*texture_we;
	mlx_image_t		*texture_ea;
	// t_FrameCounter	*frameCounter;
}					t_World_Controller;

t_World_Controller	*init_world(t_config *config);

int					init_images(t_World_Controller *world);
mlx_image_t			*init_image_mini_character(mlx_t *window,
						t_character *player, t_IntPair size);
mlx_image_t			*init_image_minimap(mlx_t *window, t_mini_map *map);

void				draw_world(t_World_Controller *world);

void				centre_character_img(t_World_Controller *world,
						t_mini_map *map, t_DoublePair pos);
void				uncentre_character_img_v(t_World_Controller *world,
						t_mini_map *map, t_DoublePair pos);
void				centre_character_img_v(t_World_Controller *world);
void				uncentre_character_img_h(t_World_Controller *world,
						t_mini_map *map, t_DoublePair pos);
void				centre_character_img_h(t_World_Controller *world);
void				raycasting(t_World_Controller *world);
int					init_textures(t_World_Controller *world, t_config *config);

#endif