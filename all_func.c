/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_func.c		                                      :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: pshandy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/8/19 12:06:35 by pshandy            #+#    #+#             */
/*   Updated: 2022/8/19 12:06:36 by pshandy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* ------------------ GET_RGB ------------------*/

int	pars_is_char_number(char *str)
{
	int	i;
	int	number;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	number = ft_atoi(str);
	if (number < 0 || number > 255)
		return (-1);
	return (number);
}

int	*pars_get_rgb(char *str)
{
	int		i;
	int		flag;
	int		*rgb;
	char	**str_arr;

	rgb = malloc(sizeof(int) * 3);
	flag = 1;
	str_arr = ft_split(str, ',');
	if (pars_char_arr_length(str_arr) != 3)
		flag = 0;
	i = -1;
	while (flag && str_arr[++i])
	{
		rgb[i] = pars_is_char_number(str_arr[i]);
		if (ft_strlen(str_arr[i]) > 3 || rgb[i] == -1)
			flag = 0;
	}
	pars_free_char_arr(str_arr);
	if (flag == 0)
	{
		free(rgb);
		return (NULL);
	}
	return (rgb);
}

/* ------------------ UTILS ------------------*/

char	*last_strstr(char *haystack, char *needle)
{
	char	*p;
	char	*result;

	if (*needle == '\0')
		return ((char *) haystack);
	result = NULL;
	while (1)
	{
		p = ft_strstr(haystack, needle);
		if (p == NULL)
			break ;
		result = p;
		haystack = p + 1;
	}
	return (result);
}

char	**add_str(char **arr, char *str)
{
	int		i;
	int		len;
	char	**new_arr;

	len = 0;
	if (arr)
		while (arr[len])
			len++;
	new_arr = malloc(sizeof(char *) * (len + 2));
	if (!new_arr)
		return (NULL);
	new_arr[len + 1] = NULL;
	new_arr[len] = str;
	i = 0;
	while (arr && arr[i] != NULL)
	{
		new_arr[i] = arr[i];
		i++;
	}
	free(arr);
	return (new_arr);
}

char	**ft_split2(char *str, char token)
{
	int		i;
	char	**arr;

	arr = malloc(sizeof(char *) * 3);
	if (!arr)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != token)
		i++;
	arr[0] = ft_substr(&str[0], 0, i);
	while (str[i] == token)
		i++;
	arr[1] = ft_substr(&str[0], i, ft_strlen(&str[i]));
	arr[2] = NULL;
	return (arr);
}

int	pars_ends_with(char *str, char *end)
{
	int		strlen;
	int		endlen;
	char	*occur;

	strlen = ft_strlen(str);
	endlen = ft_strlen(end);
	occur = last_strstr(str, end);
	if (strlen >= endlen && occur == str + (strlen - endlen))
		return (1);
	return (0);
}

int	pars_starts_with(char *str, char *pre)
{
	return (ft_strncmp(pre, str, ft_strlen(pre)) == 0);
}

int	pars_char_arr_length(char **arr)
{
	int	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

void	pars_free_char_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/* ------------------ ARGC CHECK ------------------*/

void	pars_arg_check(int argc, char **argv)
{
	if (argc != 2)
		pars_exit_with_error(BAD_ARGUMENT);
	if (!pars_ends_with(argv[1], ".cub"))
		pars_exit_with_error(BAD_EXTENSION);
}

/* ------------------ MAP PARSER ------------------*/

bool	map_is_direction(char c)
{
	return (c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}

bool	map_is_allowed_char(char c)
{
	return (c == '0' || c == '1' || map_is_direction(c) || c == ' ');
}

bool	map_is_num_direction(int c)
{
	return (c == NORTH || c == SOUTH
		|| c == EAST || c == WEST);
}

int	**map_get_empty_matrix(int rows, int cols)
{
	int	i;
	int	j;
	int	**matrix;

	i = -1;
	matrix = malloc(rows * sizeof(int *));
	while (++i < rows)
	{
		j = -1;
		matrix[i] = malloc(cols * sizeof(int));
		while (++j < cols)
			matrix[i][j] = SPACE;
	}
	return (matrix);
}

int	**map_copy_matrix(int **matrix, int rows, int cols)
{
	int		i;
	int		j;
	int		**dest;

	i = -1;
	dest = malloc(rows * sizeof(int *));
	while (++i < rows)
	{
		j = -1;
		dest[i] = malloc(cols * sizeof(int));
		while (++j < cols)
			dest[i][j] = matrix[i][j];
	}
	return (dest);
}

void	map_free_matrix(int	**matrix, int rows)
{
	int	i;

	i = -1;
	while (++i < rows)
		free(matrix[i]);
	free(matrix);
}

bool	map_is_floor(int c)
{
	return (c == NORTH || c == SOUTH
		|| c == EAST || c == WEST || c == SPACE || c == 0);
}

bool	map_is_safe(int x, int y, int **mtx, t_map *map)
{
	if (x >= 0 && x < map->rows
		&& y >= 0 && y < map->cols && (map_is_floor(mtx[x][y])))
		return (true);
	return (false);
}

void	map_dfs(int x, int y, int **mtx, t_map *map)
{
	int	k;
	int	r[4];
	int	c[4];

	r[0] = 0;
	r[1] = 0;
	r[2] = 1;
	r[3] = -1;
	c[0] = 1;
	c[1] = -1;
	c[2] = 0;
	c[3] = 0;
	mtx[x][y] = 1;
	k = -1;
	while (++k < 4)
		if (map_is_safe(x + r[k], y + c[k], mtx, map))
			map_dfs(x + r[k], y + c[k], mtx, map);
}

void	map_exclude_border(int **mtx, t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->cols)
		if (map_is_floor(mtx[0][i]))
			map_dfs(0, i, mtx, map);
	i = -1;
	while (++i < map->cols)
		if (map_is_floor(mtx[map->rows - 1][i]))
			map_dfs(map->rows - 1, i, mtx, map);
	i = -1;
	while (++i < map->rows)
		if (map_is_floor(mtx[i][0]))
			map_dfs(i, 0, mtx, map);
	i = -1;
	while (++i < map->rows)
		if (map_is_floor(mtx[i][map->cols - 1]))
			map_dfs(i, map->cols - 1, mtx, map);
}

int	map_count_all_zeros(t_map *map)
{
	int	i;
	int	j;
	int	**mtx;
	int	zeros;

	mtx = map_copy_matrix(map->matrix, map->rows, map->cols);
	map_exclude_border(mtx, map);
	i = -1;
	zeros = 0;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			if (mtx[i][j] == 0 || map_is_num_direction(mtx[i][j]))
				zeros++;
			if (mtx[i][j] == SPACE)
				map->matrix[i][j] = 0;
		}
	}
	map_free_matrix(mtx, map->rows);
	return (zeros);
}

bool	parse_map(char **str_arr, t_map *map)
{
	int		i;
	int		j;
	int		fl;
	int		al;

	i = -1;
	fl = 0;
	map->matrix = map_get_empty_matrix(map->rows, map->cols);
	while (str_arr[++i])
	{
		j = -1;
		while (str_arr[i][++j])
		{
			map->matrix[i][j] = str_arr[i][j] - '0';
			fl += (map_is_direction(str_arr[i][j]) || str_arr[i][j] == '0');
		}
	}
	al = map_count_all_zeros(map);
	if (fl != al)
	{
		map_free_matrix(map->matrix, map->rows);
		map->matrix = NULL;
	}
	return (al == fl);
}

bool	map_pre_parse(char **str_arr, t_map *map)
{
	int		j;
	bool	is_pl_set;

	map->rows = -1;
	map->cols = 0;
	is_pl_set = false;
	while (str_arr[++map->rows])
	{
		j = -1;
		while (str_arr[map->rows][++j])
		{
			if (map_is_direction(str_arr[map->rows][j]) && is_pl_set == true
				|| !map_is_allowed_char(str_arr[map->rows][j]))
				return (false);
			if (map_is_direction(str_arr[map->rows][j]) && is_pl_set == false)
			{
				is_pl_set = true;
				map->pl_x = j;
				map->pl_y = map->rows;
			}
		}
		if (j > map->cols)
			map->cols = j;
	}
	return (is_pl_set && parse_map(str_arr, map));
}

/* ------------------ CFG PARSER ------------------*/

void	pars_exit_with_error(int code)
{
	if (code == BAD_FILE)
		printf("Bad file.\n");
	else if (code == BAD_CONFIG)
		printf("Bad config.\n");
	else if (code == BAD_MAP)
		printf("Bad map.\n");
	else if (code == BAD_KEY)
		printf("Bad key.\n");
	else if (code == BAD_TEXTURE)
		printf("Bad texture.\n");
	else if (code == BAD_RGB)
		printf("Bad RGB.\n");
	else if (code == BAD_EXTENSION)
		printf("Bad extension.\n");
	else if (code == BAD_ARGUMENT)
		printf("Bad argument.\n");
	exit(1);
}

void	pars_free_all(t_cub *cub)
{
	if (cub->params.so.img != NULL)
		mlx_destroy_image(cub->mlx, cub->params.so.img);
	if (cub->params.no.img != NULL)
		mlx_destroy_image(cub->mlx, cub->params.no.img);
	if (cub->params.we.img != NULL)
		mlx_destroy_image(cub->mlx, cub->params.we.img);
	if (cub->params.ea.img != NULL)
		mlx_destroy_image(cub->mlx, cub->params.ea.img);
	if (cub->params.ce_rgb != NULL)
		free(cub->params.ce_rgb);
	if (cub->params.fl_rgb != NULL)
		free(cub->params.fl_rgb);
	if (cub->map.matrix != NULL)
		map_free_matrix(cub->map.matrix, cub->map.rows);
	free(cub->mlx);
}

int	pars_textures3(char *key, char *value, int *flags, t_cub *cub)
{
	if (!ft_strcmp(key, "EA") && !(*flags & FLAGS_EA))
	{
		*flags |= FLAGS_EA;
		cub->params.we.img = mlx_xpm_file_to_image(cub->mlx, value,
				&(cub->params.we.width), &(cub->params.we.height));
		cub->params.we.addr = mlx_get_data_addr(cub->params.we.img,
				&cub->params.we.bits_per_pixel, &cub->params.we.line_length,
				&cub->params.we.endian);
		return (0);
	}
	if (!ft_strcmp(key, "WE") && !(*flags & FLAGS_WE))
	{
		*flags |= FLAGS_WE;
		cub->params.ea.img = mlx_xpm_file_to_image(cub->mlx, value,
				&(cub->params.ea.width), &(cub->params.ea.height));
		cub->params.ea.addr = mlx_get_data_addr(cub->params.ea.img,
				&cub->params.ea.bits_per_pixel, &cub->params.ea.line_length,
				&cub->params.ea.endian);
		return (0);
	}
	return (BAD_KEY);
}

int	pars_textures2(char *key, char *value, int *flags, t_cub *cub)
{
	if (!ft_strcmp(key, "SO") && !(*flags & FLAGS_SO))
	{
		*flags |= FLAGS_SO;
		cub->params.so.img = mlx_xpm_file_to_image(cub->mlx, value,
				&(cub->params.so.width), &(cub->params.so.height));
		cub->params.so.addr = mlx_get_data_addr(cub->params.so.img,
				&cub->params.so.bits_per_pixel, &cub->params.so.line_length,
				&cub->params.so.endian);
		return (0);
	}
	if (!ft_strcmp(key, "NO") && !(*flags & FLAGS_NO))
	{
		*flags |= FLAGS_NO;
		cub->params.no.img = mlx_xpm_file_to_image(cub->mlx, value,
				&(cub->params.no.width), &(cub->params.no.height));
		cub->params.no.addr = mlx_get_data_addr(cub->params.no.img,
				&cub->params.no.bits_per_pixel, &cub->params.no.line_length,
				&cub->params.no.endian);
		return (0);
	}
	return (pars_textures3(key, value, flags, cub));
}

int	pars_textures(char *key, char *value, int *flags, t_cub *cub)
{
	int	fd;

	fd = open(value, O_RDONLY);
	if (fd == -1)
		return (BAD_TEXTURE);
	close(fd);
	if (!pars_ends_with(value, ".xpm"))
		return (BAD_TEXTURE);
	return (pars_textures2(key, value, flags, cub));
}

int	pars_rgb_value(char *key, char *value, int *flags, t_cub *cub)
{
	if (!ft_strcmp(key, "F") && !(*flags & FLAGS_F))
	{
		*flags |= FLAGS_F;
		cub->params.fl_rgb = pars_get_rgb(value);
		if (cub->params.fl_rgb == NULL)
			return (BAD_RGB);
		return (0);
	}
	if (!ft_strcmp(key, "C") && !(*flags & FLAGS_C))
	{
		*flags |= FLAGS_C;
		cub->params.ce_rgb = pars_get_rgb(value);
		if (cub->params.ce_rgb == NULL)
			return (BAD_RGB);
		return (0);
	}
	return (BAD_KEY);
}

int	pars_handle_str(char **key_value, int *flags, t_cub *cub)
{
	if (!ft_strcmp(key_value[0], "SO") || !ft_strcmp(key_value[0], "WE")
		|| !ft_strcmp(key_value[0], "EA") || !ft_strcmp(key_value[0], "NO"))
		return (pars_textures(key_value[0], key_value[1], flags, cub));
	else if (!ft_strcmp(key_value[0], "F") || !ft_strcmp(key_value[0], "C"))
		return (pars_rgb_value(key_value[0], key_value[1], flags, cub));
	else
		return (BAD_KEY);
}

int	pars_handle_cfg(char **str_arr, t_cub *cub)
{
	int		i;
	int		ret;
	int		flags;
	char	*str;
	char	**key_value;

	i = -1;
	ret = 0;
	flags = 0;
	while (str_arr[++i] && flags != ALL_FLAG && ret == 0)
	{
		if (ft_strlen(str_arr[i]) == 0)
			continue ;
		str = ft_strtrim(str_arr[i], " ");
		key_value = ft_split2(str, ' ');
		ret = pars_handle_str(key_value, &flags, cub);
		pars_free_char_arr(key_value);
		free(str);
	}
	if ((flags != ALL_FLAG || str_arr[i] == NULL) && ret == 0)
		ret = BAD_CONFIG;
	else if (ret == 0 && !map_pre_parse(&str_arr[i], &cub->map))
		ret = BAD_MAP;
	pars_free_char_arr(str_arr);
	return (ret);
}

int	pars_read_cfg(char *file, t_cub *cub)
{
	int		fd;
	char	*line;
	char	**str_arr;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (BAD_FILE);
	str_arr = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		str_arr = add_str(str_arr, ft_strtrim(line, "\n"));
		free(line);
	}
	if (str_arr == NULL)
		return (BAD_CONFIG);
	return (pars_handle_cfg(str_arr, cub));
}
