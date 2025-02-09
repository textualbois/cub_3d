/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 06:33:40 by isemin            #+#    #+#             */
/*   Updated: 2025/02/08 22:58:08 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "types_numeric.h"
# include "world.h"

t_DoublePair	ray_find_wall(t_mini_map *mini_map, t_character *player, double rayDir);
t_DoublePair	ray_find_vertical_hit(t_mini_map *mini_map, t_character *player, double rayDir, int *depth);
t_DoublePair	ray_find_horizontal_hit(t_mini_map *mini_map, t_character *player, double rayDir, int *depth);
void			increment_vertical(t_DoublePair *hit, int direction, double rayDir);
void			increment_horizontal(t_DoublePair *hit, int direction, double rayDir);
bool			is_wall(t_mini_map *mini_map, t_DoublePair hit);
t_IntPair		box_behind_border(t_DoublePair real, int mapHeight, int l_r, int u_d);

#endif