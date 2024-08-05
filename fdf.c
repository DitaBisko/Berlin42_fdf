/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:06:00 by dbisko            #+#    #+#             */
/*   Updated: 2024/07/20 21:47:42 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

# define WIDTH 500
# define HEIGHT 500

void	perspective(t_fdf *map, float z)
{
	float temp_x;
	map->angle = 0.8;

	temp_x = (map->x - map->y) * (float)cos(map->angle);
	map->y = (map->x + map->y) * (float)sin(map->angle) - z;
	map->x = temp_x;
}

void	draw_line(t_fdf *map)
{
	float 	x_step;
	float 	y_step;
	float 	max;
	int 	color;

	map->x = map->x * map->zoom;
	map->y = map->y * map->zoom;
	map->x1 = map->x1 * map->zoom;
	map->y1 = map->y1 * map->zoom;

	if (map->z > 0)
		color = 0x0000FFFF;
	else
		color = 0xFFFFFFFF;

	ft_printf("Before perspective: x=%d, y=%d, x1=%d, y1=%d\n", map->x, map->y, map->x1, map->y1);
	perspective(map, map->z);
	perspective(map, map->z1);

	x_step = map->x1 - map->x;
	if (x_step < 0)
		x_step = x_step * - 1;
	y_step = map->y1 - map->y;
	if (y_step < 0)
		y_step = y_step * - 1;
	if (x_step > y_step)
		max = x_step;
	else
		max = y_step;

	x_step = x_step / max;
	y_step = y_step / max;

	while((int)(map->x -map->x1) || (int)(map->y -map->y1))
	{
		mlx_put_pixel(map->img, (unsigned int)map->x, (unsigned int)map->y, color);
		map->x = map->x + x_step;
		map->y = map->y + y_step;
	}
}

void	draw(t_fdf *map)
{
	float x;
	float y;

	y = 0.0;
	while(y < map->height)
	{
		ft_printf("y:%d\n", y);
		x = 0.0;
		while (x < map->width)
		{
			ft_printf("x:%d\n", x);
			if (x < map->width - 1)
			{
				map->x = x;
				map->y = y;
				map->x1 = x + 1.0;
				map->y1 = y;
				map->z = (float)map->arr_map[(int)y][(int)x];
				map->z1 = (float)map->arr_map[(int)y][(int)x+1];
				draw_line(map);
			}
			if (y < map->height - 1)
			{
				map->x = x;
				map->y = y;
				map->x1 = x;
				map->y1 = (y + 1.0);
				map->z = (float)map->arr_map[(int)y][(int)x];
				map->z1 = (float)map->arr_map[(int)y+1][(int)x];
				draw_line(map);
			}
			x = x + 1.0;
		}
		y = y + 1.0;
	}
}

int	main(int ac, char **av)
{
	t_fdf	*map;

	if (ac != 2)
		return_error("Usage: ./fdf <filename>\n");
	map = malloc(sizeof(t_fdf));
	if (map == NULL)
		return_error("Error: map malloc fail\n");
	parse_file(av[1], map);
	map->mlx = mlx_init(WIDTH, HEIGHT, "FDF", true);
	if (!map->mlx)
		return_error("MLX42 initialization failed\n");
	map->img = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	if (!map->img)
		return_error("Failed to create image\n");
	// draw to image mlx_put_pixel(img, x, y, color);
	map->zoom = 20;
	draw(map);
	mlx_image_to_window(map->mlx, map->img, 0, 0);
	mlx_loop(map->mlx);
	mlx_terminate(map->mlx);
	free(map);
	return 0;
}
