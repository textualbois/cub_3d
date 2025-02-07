/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:12:18 by isemin            #+#    #+#             */
/*   Updated: 2025/02/08 00:37:42 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

#include "MLX42/MLX42.h"
#include "character.h"
#include "fps.h"
#include "window.h"
#include "mini_map.h"
#include "draw.h"
#include "./parser/parser.h"

typedef struct s_World_Controller{
	mlx_t			*window;
	t_IntPair		size;
	t_character		*player;
	t_mini_map		*map; // mini_map?
	t_map			mapp; // namings..
	//int				map[8][8]; // change to t_map?
	mlx_image_t		*map_img;
	mlx_image_t		*miniCharacter;
	//t_FrameCounter	*frameCounter;
}	t_World_Controller;

t_World_Controller	*init_world(t_map map);

int					init_images(t_World_Controller *world);//, int map[8][8]);
mlx_image_t			*init_image_mini_character(mlx_t *window, t_character *player, t_IntPair size);
mlx_image_t			*init_image_minimap(mlx_t *window, t_mini_map *map);//, int map[8][8]);

void				draw_world(t_World_Controller *world);

void centre_character_img(t_World_Controller *world, t_mini_map *map, t_DoublePair pos);
void uncentre_character_img_v(t_World_Controller *world, t_mini_map *map, t_DoublePair pos);
void centre_character_img_v(t_World_Controller *world);
void uncentre_character_img_h(t_World_Controller *world, t_mini_map *map, t_DoublePair pos);
void centre_character_img_h(t_World_Controller *world);


#endif