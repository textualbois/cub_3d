/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:09:33 by admin             #+#    #+#             */
/*   Updated: 2025/02/07 14:33:42 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_DoublePair
{
	double			x;
	double			y;
}					t_DoublePair;

typedef struct s_IntPair
{
	int				x;
	int				y;
}					t_IntPair;

typedef struct s_character
{
	t_IntPair		size;
	t_DoublePair	pos;
	float			angle;
}					t_character;

typedef struct s_map
{
	char			**grid;
	int				width;
	int				height;
}					t_map;

typedef struct s_config
{
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	int				floor_color[3];
	int				ceiling_color[3];
	int				has_no;
	int				has_so;
	int				has_we;
	int				has_ea;
	int				has_floor;
	int				has_ceiling;
	t_map			map;
	t_character		player;
}					t_config;

# define BUFFER_SIZE 4096

// parser_free_utils.c
void				free_config(t_config *config);

void				free_lines(char **lines);

// parse_color_utils.c

int					validate_and_convert_color(char **rgb, int *color);

// parse_color.c
int					parse_ceiling_color(char *trimmed, t_config *config);
int					parse_floor_color(char *trimmed, t_config *config);

void				free_split_lines(char ***lines);

#endif
