/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:31:05 by dbisko            #+#    #+#             */
/*   Updated: 2024/07/31 20:54:57 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	ft_f_abs(float a)
{
	if (a < 0)
		return (-a);
	else
		return (a);
}

int	ft_i_abs(int a)
{
	if (a < 0)
		return (-a);
	else
		return (a);
}

float	calculate_max(float x_step, float y_step)
{
	float	abs_x;
	float	abs_y;

	abs_x = ft_f_abs(x_step);
	abs_y = ft_f_abs(y_step);
	if (abs_x > abs_y)
		return (abs_x);
	else
		return (abs_y);
}

// Applies perspective projection to 3D coordinates flattening them to 2D
void	perspective(float *x, float *y, float z, t_fdf *map)
{
	float	temp;

	temp = *x;
	*x = (temp - *y) * cos(map->angle);
	*y = (temp + *y) * sin(map->angle) - z;
}

void	set_min_max_coordinates(t_fdf *map)
{
	map->min_x = 1e30;
	map->max_x = -1e30;
	map->min_y = 1e30;
	map->max_y = -1e30;
}

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

// Offset Calculation: Computes offsets to center the map on the screen.
void	calculate_offset(t_fdf *map)
{
	calculate_box(map);
	map->map_width = (map->max_x - map->min_x) * map->zoom;
    map->map_height = (map->max_y - map->min_y) * map->zoom;
 	map->offset_x = (WIDTH - map->map_width) / 2 - (map->min_x * map->zoom);
    map->offset_y = (HEIGHT - map->map_height) / 2 - (map->min_y * map->zoom);

}

void	put_line_to_image(t_fdf *map)
{
	float	x_step;
	float	y_step;
	float	max;
	float	x;
	float	y;

	x = map->x;
	y = map->y;
	max = calculate_max((map->x1 - x), (map->y1 - y));
	x_step = (map->x1 - x) / max;
	y_step = (map->y1 - y) / max;
	map->total_len = sqrtf((map->x1 - x) * (map->x1 - x)
			+ (map->y1 - y) * (map->y1 - y));
	while (ft_f_abs(x - map->x1) > 0.5 || ft_f_abs(y - map->y1) > 0.5)
	{
		map->distance_traveled = sqrtf((map->x1 - x) * (map->x1 - x)
				+ (map->y1 - y) * (map->y1 - y));
		if ((y >= 0 && y < HEIGHT) && (x >= 0 && x < HEIGHT))
			map->pixel_data[(int)roundf(y) * WIDTH + (int)roundf(x)]
				= calculate_color_put_pixel(map);
		x = x + x_step;
		y = y + y_step;
	}
}

void	draw_horizontal(int row, int col, t_fdf *map)
{
	float	x;
	float	y;
	float	z;

	x = (float)(col + 1);
	y = (float)row;
	z = (float)map->arr_map[row][col + 1];
	perspective(&x, &y, z, map);
	x = (x * map->zoom) + map->offset_x;
	y = (y * map->zoom) + map->offset_y;
	map->x1 = x;
	map->y1 = y;
	map->color_to = map->arr_color[row][col + 1];
	put_line_to_image(map);
}

void	draw_vertical(int row, int col, t_fdf *map)
{
	float	x;
	float	y;
	float	z;

	x = (float)col;
	y = (float)(row + 1);
	z = (float)map->arr_map[row + 1][col];
	perspective(&x, &y, z, map);
	x = (x * map->zoom) + map->offset_x;
	y = (y * map->zoom) + map->offset_y;
	map->x1 = x;
	map->y1 = y;
	map->color_to = map->arr_color[row + 1][col];
	put_line_to_image(map);
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

// Draws lines between adjacent points,
// handling horizontal and vertical connections.
void	draw_lines(t_fdf *map)
{
	int	row;
	int	col;

	row = 0;
	while (row < map->arr_height)
	{
		col = 0;
		while (col < map->arr_width)
		{
			set_and_transform_xy(map, col, row);
			if (map->x >= 0 && map->x < WIDTH && map->y >= 0 && map->y < HEIGHT)
			{
				if (col < map->arr_width -1)
					draw_horizontal(row, col, map);
				if (row < map->arr_height -1)
					draw_vertical(row, col, map);
			}
			col++;
		}
		row++;
	}
}

// Manages image creation, line drawing, and display on the window.
void	draw(t_fdf *map)
{
	map->img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	map->pixel_data = (int *) mlx_get_data_addr(map->img,
			&map->bpp, &map->size_line, &map->endian);
	calculate_offset(map);
	draw_lines(map);
	mlx_put_image_to_window(map->mlx, map->win, map->img, 0, 0);
}


/*
void	reverse_color_direction(t_fdf *map)
{
	int	temp;

	if (map->y > map->y1)
	{
		temp = map->color_from;
		map->color_from = map->color_to;
		map->color_to = temp;
	}
}
*/