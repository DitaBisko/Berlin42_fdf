/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:01:57 by dbisko            #+#    #+#             */
/*   Updated: 2024/07/20 15:01:57 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	set_max_min_z(t_fdf *map)
{
	int	row;
	int	col;
	int	max;
	int	min;

	max = map->arr_map[0][0];
	min = map->arr_map[0][0];
	row = 0;
	while (row < map->arr_height)
	{
		col = 0;
		while (col < map->arr_width)
		{
			if (map->arr_map[row][col] < min)
				min = map->arr_map[row][col];
			if (map->arr_map[row][col] > max)
				max = map->arr_map[row][col];
			col++;
		}
		row++;
	}
	map->min_z = min;
	map->max_z = max;
}

void	allocate_mem_arr(t_fdf *map)
{
	int	y;

	map->arr_map = malloc(map->arr_height * sizeof (int *));
	if (map->arr_map == NULL)
		return_error("Error: map y position malloc fail\n");
	y = 0;
	while (y < map->arr_height)
	{
		map->arr_map[y] = malloc(map->arr_width * sizeof(int));
		if (map->arr_map[y] == NULL)
			free_int_arr(map->arr_map, y);
		y++;
	}
}

int	place_values(t_fdf *map, char **split_line, int row)
{
	int	col;

	col = 0;
	while (col < map->arr_width)
	{
		map->arr_map[row][col] = ft_atoi(split_line[col]);
		col++;
	}
	return (col);
}

void	fill_arr_map(char *file, t_fdf *map)
{
	int		fd;
	int		row;
	int		col;
	char	*line;
	char	**split_line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return_error("Error: opening file\n");
	line = get_next_line(fd);
	row = 0;
	while (line != NULL)
	{
		split_line = ft_split(line, ' ');
		col = place_values(map, split_line, row);
		free_split_line(split_line, col);
		free(line);
		line = get_next_line(fd);
		row++;
	}
	free(line);
	close(fd);
}

void	parse_file(char *file, t_fdf *map)
{
	map->arr_height = 0;
	map->arr_width = 0;
	map->arr_height = (float)map_height(file);
	map->arr_width = (float)map_width(file);
	allocate_mem_arr(map);
	fill_arr_map(file, map);
	set_max_min_z(map);
	fill_color_arr(file, map);
}
