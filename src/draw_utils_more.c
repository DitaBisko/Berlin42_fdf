/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_more.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:31:05 by dbisko            #+#    #+#             */
/*   Updated: 2024/07/31 20:54:57 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	update_min_max_xy(float x, float y, t_fdf *map)
{
	if (x < map->min_x)
		map->min_x = x;
	if (x > map->max_x)
		map->max_x = x;
	if (y < map->min_y)
		map->min_y = y;
	if (y > map->max_y)
		map->max_y = y;
}

// Determines the minimum and maximum x and y
// coordinates of the transformed map.
void	calculate_box(t_fdf *map)
{
	int		col;
	int		row;
	float	x;
	float	y;
	float	z;

	row = 0;
	set_min_max_coordinates(map);
	while (row < map->arr_height)
	{
		col = 0;
		while (col < map->arr_width)
		{
			x = (float)col;
			y = (float)row;
			z = (float)map->arr_map[row][col];
			perspective(&x, &y, z, map);
			update_min_max_xy(x, y, map);
			col++;
		}
		row++;
	}
}

// Computes offsets to center the map on the screen

void	calculate_offset(t_fdf *map)
{
	calculate_box(map);
	map->map_width = (map->max_x - map->min_x) * map->zoom;
	map->map_height = (map->max_y - map->min_y) * map->zoom;
	map->offset_x = (WIDTH - map->map_width) / 2 - (map->min_x * map->zoom);
	map->offset_y = (HEIGHT - map->map_height) / 2 - (map->min_y * map->zoom);
}

void	set_and_transform_xy(t_fdf *map, int col, int row)
{
	float	x;
	float	y;
	float	z;

	x = (float)col;
	y = (float) row;
	z = (float)map->arr_map[row][col];
	perspective(&x, &y, z, map);
	map->x = (x * map->zoom) + map->offset_x;
	map->y = (y * map->zoom) + map->offset_y;
	map->color_from = map->arr_color[row][col];
}
