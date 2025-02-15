/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 13:28:00 by admin             #+#    #+#             */
/*   Updated: 2025/02/15 16:57:01 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_TEXTURES_H
# define DRAW_TEXTURES_H

# include "MLX42/MLX42.h"
# include "character.h"
# include "world.h"
# include <math.h>

# define MAX_PITCH (50.0 * (PI / 180.0))
/*
** t_line - структура для параметров вертикальной линии,
	которая будет отрисована.
**  x      - координата столбца (на экране),
**  top    - верхняя граница отрисовки столбца,
**  bottom - нижняя граница отрисовки столбца.
*/
typedef struct s_line
{
	int			x;
	int			top;
	int			bottom;
}				t_line;

/*
** t_tex_line - структура для параметров текстурной линии.
**  texture  - указатель на текстуру стены (MLX42 изображение),
**  textureX - горизонтальная координата текстуры (от 0 до 1), определяющая,
	какой столбец текстуры брать.
*/
typedef struct s_tex_line
{
	mlx_image_t	*texture;
	double		textureX;
}				t_tex_line;

/*
** t_ray - структура для параметров луча (используется при raycasting'е).
**  perpWallDist - перпендикулярное расстояние до стены,
**  rayDirX      - X-компонента направления луча,
**  rayDirY      - Y-компонента направления луча,
**  side         - 0, если удар произошёл по вертикальной стороне; 1,
	если по горизонтальной.
*/
typedef struct s_ray
{
	double		perpWallDist;
	double		rayDirX;
	double		rayDirY;
	int			side;
}				t_ray;

/*
** t_draw3d_params - структура для параметров отрисовки 3D-стены.
**  world3d - указатель на изображение 3D-сцены,
**  player
	- указатель на персонажа (используется для вычисления координаты текстуры),
**  x       - координата столбца на экране, где рисуется стена.
*/
typedef struct s_draw3d_params
{
	mlx_image_t	*world3d;
	t_character	*player;
	int			x;
}				t_draw3d_params;

/*
** Прототипы функций, которые будут использовать данные структуры.
** Реализация будет добавлена в следующих коммитах.
*/
void			draw_textured_vertical_line(mlx_image_t *img, t_line line,
					t_tex_line tex_line);
double			compute_texture_x(t_character *player, t_ray ray);
void			draw3d(t_draw3d_params *params, t_ray ray,
					t_World_Controller *world);
#endif
