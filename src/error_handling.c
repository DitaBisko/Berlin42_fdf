/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:14:06 by dbisko            #+#    #+#             */
/*   Updated: 2024/08/04 17:05:58 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	return_error(char *err_message, t_fdf *map)
{
	ft_printf("%s", err_message);
	free_fdf(map);
	exit (1);
}

void	free_int_arr(int **arr, int count)
{
	int	i;

	i = 0;
	if (arr != NULL)
	{
		while (i < count)
		{
			if (arr[i] != NULL)
				free(arr[i]);
			i++;
		}
	}
	free(arr);
}

void	free_split_line(char **split_line, int i)
{
	if (split_line != NULL)
	{
		while (i >= 0)
		{
			if (split_line[i] != NULL)
				free(split_line[i]);
			i--;
		}
	}
	free(split_line);
}

void	safe_free_line(char *line)
{
	if (line != NULL)
		free(line);
}

int	free_fdf(t_fdf *map)
{
	mlx_destroy_image(map->mlx, map->img);
	mlx_destroy_window(map->mlx, map->win);
	mlx_destroy_display(map->mlx);
	if (map->mlx != NULL)
		free(map->mlx);
	if (map->arr_map != NULL)
		free_int_arr(map->arr_map, map->arr_height);
	if (map->arr_color != NULL)
		free_int_arr(map->arr_color, map->arr_height);
	if (map != NULL)
		free(map);
	exit (0);
}
