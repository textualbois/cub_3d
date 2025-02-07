/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 14:09:33 by admin             #+#    #+#             */
/*   Updated: 2025/02/08 00:18:32 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include "../character.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
}				t_map;

typedef struct s_config
{
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			floor_color[3];
	int			ceiling_color[3];
	int			has_no;
	int			has_so;
	int			has_we;
	int			has_ea;
	int			has_floor;
	int			has_ceiling;
	t_map		map;
	t_character	player;
}				t_config;

# define BUFFER_SIZE 4096

// parser_free_utils.c
void			free_config(t_config *config);

void			free_lines(char **lines);

// parse_color_utils.c

int				validate_and_convert_color(char **rgb, int *color);

// parse_color.c
int				parse_ceiling_color(char *trimmed, t_config *config);
int				parse_floor_color(char *trimmed, t_config *config);

// string_utils.c
void			free_split_lines(char ***lines);
char			**split_lines_manual(char *file_content);
// file_utils.c
int				parse_cub_file(const char *filename, t_config *config);
// libft_utils.c
char			*pad_line(char *line, int width);
int				skip_empty_lines(char **lines);
int				ft_isspace(char c);
char			*trim_and_validate_line(char *line);
// parse_textures_colors.c
char			**parse_textures_colors(char **lines, t_config *config);

// parse_line.c
int				parse_line(char *line, t_config *config);
// validate_map.c
int				validate_map_structure(t_map *map, t_config *config);
// validate_map_utils.c
int				is_valid_cell(t_map *map, int i, int j);

int				is_sur_by_wals(t_map *map, int i, int j);

int				is_valid_map_char(char c);

void			set_player_position(t_config *config, int x, int y, char dir);
// parser.c
char			**parse_map(char **lines, t_config *config);
#endif
