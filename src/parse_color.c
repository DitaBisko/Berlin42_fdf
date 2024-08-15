/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:12:13 by dbisko            #+#    #+#             */
/*   Updated: 2024/07/25 16:12:13 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	allocate_mem_color(t_fdf *map)
{
	int	y;

	map->arr_color = malloc(map->arr_height * sizeof(int *));
	if (map->arr_color == NULL)
		return_error("Error: map y position malloc fail\n", map);
	y = 0;
	while (y < map->arr_height)
	{
		map->arr_color[y] = malloc(map->arr_width * sizeof(int));
		if (map->arr_color[y] == NULL)
			free_int_arr(map->arr_color, y);
		y++;
	}
}

int	calculate_color(int z_value, t_fdf *map)
{
	int		red;
	int		green;
	int		blue;
	float	ratio;

	if (z_value == map->max_z)
		return (map->max_color);
	if (z_value == map->min_z)
		return (map->min_color);
	ratio = (((float)z_value - (float)map->min_z)
			/ ((float)map->max_z - (float)map->min_z));
	red = adjust_red(map->min_color, map->max_color, ratio);
	green = adjust_green(map->min_color, map->max_color, ratio);
	blue = adjust_blue(map->min_color, map->max_color, ratio);
	return ((red << 16) | (green << 8) | blue);
}

void	extract_color(char *line, t_fdf *map, int row)
{
	int		col;
	char	**split_line;
	char	**split_color;

	col = 0;
	split_line = ft_split(line, ' ');
	while (split_line[col] != NULL && col < map->arr_width)
	{
		if (ft_strchr(split_line[col], ',') != NULL)
		{
			split_color = ft_split(split_line[col], ',');
			map->arr_color[row][col] = hex_to_int(split_color[1]);
			free_split_line(split_color, 1);
		}
		else
			map->arr_color[row][col]
				= calculate_color(map->arr_map[row][col], map);
		col++;
	}
	free_split_line(split_line, col);
}

void	fill_color_arr(char *file, t_fdf *map)
{
	int		fd;
	int		row;
	char	*line;

	map->max_color = 65535;
	map->min_color = 32768;
	allocate_mem_color(map);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return_error("Error: opening file\n", map);
	line = get_next_line(fd);
	row = 0;
	while (line != NULL)
	{
		extract_color(line, map, row);
		safe_free_line(line);
		line = get_next_line(fd);
		row++;
	}
	safe_free_line(line);
	close(fd);
}
