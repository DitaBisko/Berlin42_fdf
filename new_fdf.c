/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_fdf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 09:27:04 by dbisko            #+#    #+#             */
/*   Updated: 2024/07/23 10:37:47 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <signal.h>

void	print_arr_values(t_fdf *map)
{
	int	row;

	row = 0;
	while (row < map->arr_height)
	{
		int	col = 0;
		while (col < map->arr_width)
		{
			printf("%3d", map->arr_map[row][col]);
			if (col == map->arr_width -1)
				printf("\n");
			col++;
		}
		row++;
	}
}

void	print_arr_colors(t_fdf *map)
{
	int row = 0;
	while (row < map->arr_height)
	{
		int	col = 0;
		while (col < map->arr_width)
		{
			printf("%10d", map->arr_color[row][col]);
			if (col == map->arr_width -1)
				printf("\n");
			col++;
		}
		row++;
	}
}

int	handle_input(int key_code, t_fdf *map)
{
	if (key_code == 65307)
	{
		free_fdf(map);
		exit (1);
	}
	return (0);
}

int	close_win(t_fdf *map)
{
	free_fdf(map);
	return (0);
}

void	init_map(t_fdf *map, char *str)
{
	map->mlx = mlx_init();
	if (!map->mlx)
		return_error("MLX initialization failed\n");
	map->win = mlx_new_window(map->mlx, WIDTH, HEIGHT, str);
}

int	main(int ac, char **av)
{
	t_fdf	*map;

	if (ac != 2)
		return_error("Usage: ./fdf <filename>\n");
	printf("Process started\n");
	map = malloc(sizeof (t_fdf));
	if (!map)
		return_error("Error: map malloc fail\n");
	printf("Memmory allocated for map\n");
	parse_file(av[1], map);
	print_arr_values(map);
	init_map(map, av[1]);
	mlx_hook(map->win, 17, 0L, close_win, map);
	map->zoom = 10;
	map->angle = 0.523599;
	draw(map);
	mlx_hook(map->win, 2, 1L << 0, handle_input, map);
	mlx_loop(map->mlx);
	free_fdf(map);
	exit (0);
}
