/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 06:33:40 by isemin            #+#    #+#             */
/*   Updated: 2025/02/09 22:40:15 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "types_numeric.h"
# include "world.h"

typedef struct s_Collision {
	int				type;
	t_DoublePair	hit;
}	t_Collision;

t_DoublePair	ray_find_wall(t_mini_map *mini_map, t_character *player, double rayDir);
t_DoublePair	ray_find_vertical_hit(t_mini_map *mini_map, t_character *player, double rayDir, t_IntPair direction);
t_DoublePair	ray_find_horizontal_hit(t_mini_map *mini_map, t_character *player, double rayDir, t_IntPair direction);
void			increment_vertical(t_DoublePair *hit, int direction, double rayDir);
void			increment_horizontal(t_DoublePair *hit, int direction, double rayDir);
bool			is_wall(t_mini_map *mini_map, t_DoublePair hit, t_IntPair direction, int caller);
t_IntPair		box_behind_border(t_DoublePair real, int mapHeight, int l_r, int u_d);

t_Collision		collision_find_wall(t_mini_map *mini_map, t_character *player, double rayDir);
t_DoublePair	collision_find_vertical_hit(t_mini_map *mini_map, t_character *player, double rayDir, t_IntPair direction);
t_DoublePair	collision_find_horizontal_hit(t_mini_map *mini_map, t_character *player, double rayDir, t_IntPair direction);

#endif