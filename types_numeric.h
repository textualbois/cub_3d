/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_numeric.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:12:10 by isemin            #+#    #+#             */
/*   Updated: 2025/02/09 22:38:51 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_NUMERIC_H
# define TYPES_NUMERIC_H

#include <math.h>
#include <stdlib.h>

// default window size
#define WIDTH 800
#define HEIGHT 800
#define VISIBLE_TILES 8 // later maybe make it 16
#define PPU 10 // pixels per unit
#define PI 3.1415926
#define FOV 60
#define LOD 20
#define TILE_SIZE 10
#define VERTICAL 1
#define HORIZONTAL 0

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