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

#include "fdf.h"

int	count_digits(char *str)
{
	int	digit_flag;
	int	count;

	count = 0;
	digit_flag = 0;
	while (*str != '\0' && *str != '\n')
	{
		if (*str != ' ')
		{
			if (digit_flag == 0)
			{
				count++;
				digit_flag = 1;
			}
		}
		else
			digit_flag = 0;
		str++;
	}
	return (count);
}

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

void	fill_arr_map(char *file, t_fdf *map)
{
	int		fd;
	int		y;
	int		x;
	char	*line;
	char	**split_line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return_error("Error: opening file\n");
	line = get_next_line(fd);
	y = 0;
	while (line != NULL)
	{
		x = 0;
		split_line = ft_split(line, ' ');
		while (split_line[x] != NULL)
		{
			map->arr_map[y][x] = ft_atoi(split_line[x]);
			x++;
		}
		free_split_line(split_line, x);
		safe_free_line(line);
		line = get_next_line(fd);
		y++;
	}
	safe_free_line(line);
	close(fd);
}

void	parse_file(char *file, t_fdf *map)
{
	map->arr_height = map_height(file);
	map->arr_width = map_width(file);
	allocate_mem_arr(map);
	fill_arr_map(file, map);
	set_max_min_z(map);
	fill_color_arr(file, map);
}
