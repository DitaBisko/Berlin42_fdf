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

#include "../include/fdf.h"

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
	while (ft_f_abs(x - map->x1) > 0.5 || ft_f_abs(y - map->y1) > 0.5)
	{
		if ((y >= 20 && y < HEIGHT - 20) && (x >= 20 && x < WIDTH - 20))
			map->pixel_data[(int)roundf(y) * WIDTH + (int)roundf(x)]
				= map->color_from;
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
