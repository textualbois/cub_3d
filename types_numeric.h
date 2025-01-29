/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_numeric.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:12:10 by isemin            #+#    #+#             */
/*   Updated: 2025/01/29 08:19:45 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_NUMERIC_H
# define TYPES_NUMERIC_H

#include <math.h>
#include <stdlib.h>

// default window size
#define WIDTH 800
#define HEIGHT 800
#define PI 3.14159265
#define FOV 60
#define LOD 20

typedef struct s_IntPair{
	int32_t x;
	int32_t y;
}	t_IntPair;

typedef struct s_IntPtrPair{
	int32_t *x;
	int32_t *y;
}	t_IntPtrPair;

typedef struct s_DoublePair{
	double x;
	double y;
}	t_DoublePair;

typedef struct s_DoublePtrPair{
	double *x;
	double *y;
}	t_DoublePtrPair;

#endif