/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:30 by isemin            #+#    #+#             */
/*   Updated: 2025/02/17 12:03:29 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_H
# define CHARACTER_H

# include "MLX42/MLX42.h"
# include "malloc_counter.h"
# include "types_common.h"

t_character	*init_mini_character(t_IntPair size, t_character player);

void		ft_color_mini_character_direction(mlx_image_t *character, int color,
				t_character *player);
void		ft_color_mini_character(mlx_image_t *player, int color);

#endif