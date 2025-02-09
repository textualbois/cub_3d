/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:30 by isemin            #+#    #+#             */
/*   Updated: 2025/02/09 11:16:33 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_H
# define CHARACTER_H

#include "MLX42/MLX42.h"
#include "types_numeric.h"
// #include "world.h"

typedef struct s_character{
	t_IntPair size;
	t_DoublePair pos;
	double angle;
}	t_character;

// init
t_character	*init_mini_character(t_IntPair size, t_character player);

// free

// move

// draw

void ft_color_mini_character_direction(mlx_image_t *character, int color, t_character *player);
void ft_color_mini_character(mlx_image_t *player, int color);


#endif