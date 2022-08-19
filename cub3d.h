/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h		                                      :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/8/19 12:06:35 by pshandy            #+#    #+#             */
/*   Updated: 2022/8/19 12:06:36 by pshandy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define FLAGS_NO 1 // 1U <<  0U
# define FLAGS_SO 2 // 1U <<  1U
# define FLAGS_WE 4 // 1U <<  2U
# define FLAGS_EA 8 // 1U <<  3U
# define FLAGS_F  16 // 1U << 4U
# define FLAGS_C  32 // 1U << 5U
# define ALL_FLAG 63 // 111111

# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

# include "./mlx_linux/mlx.h"
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"

enum e_map_elem
{
	SPACE = -16,
	FLOOR = 0,
	WALL = 1,
	EAST = 21,
	NORTH = 30,
	SOUTH = 35,
	WEST = 39
};

enum e_error
{
	BAD_FILE = 1,
	BAD_CONFIG = 2,
	BAD_MAP = 3,
	BAD_KEY = 4,
	BAD_TEXTURE = 5,
	BAD_RGB = 6,
	BAD_EXTENSION = 7,
	BAD_ARGUMENT = 8
};

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_texture;

typedef struct s_params
{
	t_texture		so;
	t_texture		no;
	t_texture		we;
	t_texture		ea;
	int				*fl_rgb;
	int				*ce_rgb;
}					t_params;

typedef struct s_map
{
	int	rows;
	int	cols;
	int	pl_x;
	int	pl_y;
	int	**matrix;
}	t_map;

typedef struct s_cub
{
	void			*mlx;
	void			*win;
	t_params		params;
	t_map			map;
}					t_cub;

/* GET RGB */
int		pars_is_char_number(char *str);
int		*pars_get_rgb(char *str);

/* UTILS */
int		pars_ends_with(char *str, char *end);
int		pars_starts_with(char *str, char *pre);
int		pars_char_arr_length(char **arr);
char	*last_strstr(char *haystack, char *needle);
char	**add_str(char **arr, char *str);
char	**ft_split2(char *str, char token);
void	pars_free_char_arr(char **arr);

/* ARGC CHECK */
void	pars_arg_check(int argc, char **argv);

/* MAP PARSING */
int		map_count_all_zeros(t_map *map);
int		**map_get_empty_matrix(int rows, int cols);
int		**map_copy_matrix(int **matrix, int rows, int cols);
void	map_free_matrix(int	**matrix, int rows);
void	map_dfs(int x, int y, int **mtx, t_map *map);
void	map_exclude_border(int **mtx, t_map *map);
bool	map_is_direction(char c);
bool	map_is_allowed_char(char c);
bool	map_is_num_direction(int c);
bool	map_is_floor(int c);
bool	map_is_safe(int x, int y, int **mtx, t_map *map);
bool	parse_map(char **str_arr, t_map *map);
bool	map_pre_parse(char **str_arr, t_map *map);

/* CFG PARSING */
int		pars_textures(char *key, char *value, int *flags, t_cub *cub);
int		pars_textures2(char *key, char *value, int *flags, t_cub *cub);
int		pars_textures3(char *key, char *value, int *flags, t_cub *cub);
int		pars_read_cfg(char *file, t_cub *cub);
int		pars_handle_str(char **key_value, int *flags, t_cub *cub);
int		pars_rgb_value(char *key, char *value, int *flags, t_cub *cub);
void	pars_free_all(t_cub *cub);
void	pars_exit_with_error(int code);
#endif
