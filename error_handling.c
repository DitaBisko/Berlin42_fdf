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

#include "fdf.h"

void	return_error(char *err_message)
{
	perror(err_message);
	exit (1);
}

void	free_int_arr(int **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_split_line(char **split_line, int i)
{
	if (split_line != NULL)
	{
		while (i > -1)
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

void free_fdf(t_fdf *map)
{
    if (map == NULL)
        return;

    if (map->arr_map != NULL)
    {
        free_int_arr(map->arr_map, map->arr_height);
        map->arr_map = NULL; // Prevent double free
    }
    if (map->arr_color != NULL)
    {
        free_int_arr(map->arr_color, map->arr_height);
        map->arr_color = NULL; // Prevent double free
    }
    if (map->pixel_data != NULL)
    {
        free(map->pixel_data);
        map->pixel_data = NULL; // Prevent double free
    }

    if (map->img != NULL)
    {
        mlx_destroy_image(map->mlx, map->img);
        map->img = NULL; // Prevent double free
    }
    if (map->win != NULL)
    {
        mlx_destroy_window(map->mlx, map->win);
        map->win = NULL; // Prevent double free
    }
    if (map->mlx != NULL)
    {
        mlx_destroy_display(map->mlx); // This is often not necessary
        map->mlx = NULL; // Prevent double free
    }

    free(map); // Free the structure itself
}
