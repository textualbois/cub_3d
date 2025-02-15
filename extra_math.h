/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_math.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:42:08 by isemin            #+#    #+#             */
/*   Updated: 2025/02/15 19:33:51 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTRA_MATH_H
# define EXTRA_MATH_H

# include "types_numeric.h"

double	distance(t_DoublePair a, t_DoublePair b);
double	ceil_map(double x);
double	floor_map(double x);
t_DoublePair	add_pair(t_DoublePair a, t_DoublePair b);
double normalise_radians(double angle);

#endif