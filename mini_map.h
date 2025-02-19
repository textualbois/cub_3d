/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:11:59 by isemin            #+#    #+#             */
/*   Updated: 2025/02/19 18:04:08 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_MAP_H
# define MINI_MAP_H

# include "MLX42/MLX42.h"
# include "character.h"
# include "libft/libft.h"
# include "malloc_counter.h"
# include "parser/parser.h"
# include "types_common.h"

t_mini_map	*init_minimap(t_config *config);
void		centre_mini_map(t_mini_map *map, t_character *player);

#endif
