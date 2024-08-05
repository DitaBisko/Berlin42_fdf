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

int count_digits(char *str)
{
	int digit_flag;
	int count;

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

int	map_height(char *file)
{
	char 	*line;
	int 	fd;
	int 	count;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return_error("Error: opening file\n");
	line = get_next_line(fd);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (count);
}

int	map_width(char *file)
{
	int fd;
	int count;
	char *line;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return_error("Error: opening file\n");
	line = get_next_line(fd);
	count = count_digits(line);
	while(line)
	{
		get_next_line(fd);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (count);
}

void	allocate_mem_map_arr(t_fdf *map)
{
	int y;

	map->arr_map = malloc(map->height * sizeof(int*));
	if (map->arr_map == NULL)
		return_error("Error: map y position malloc fail\n");
	y = 0;
	while(y < map->height)
	{
		map->arr_map[y] = malloc(map->width * sizeof(int));
		if (map->arr_map[y] == NULL)
		{
			free_int_arr(map->arr_map, y);
			return_error("Error: map x position malloc fail\n");
		}
		y++;
	}
}

void	fill_map_arr(char *file, t_fdf *map)
{
	int		fd;
	int 	y;
	int 	x;
	char 	*line;
	char 	**split_line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return_error("Error: opening file\n");
	allocate_mem_map_arr(map);
	line= get_next_line(fd);
	y = 0;
	while(line)
	{
		x = 0;
		split_line = ft_split(line, ' ');
		while(*split_line)
		{
			map->arr_map[y][x] = ft_atoi(*split_line);
			x++;
			split_line++;
		}
		free(line);
		line= get_next_line(fd);
		y++;
	}
	close(fd);
}

void	parse_file(char *file, t_fdf *map)
{
	map->height = map_height(file);
	map->width = map_width(file);
	fill_map_arr(file, map);
}