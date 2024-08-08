/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:03:44 by dbisko            #+#    #+#             */
/*   Updated: 2024/07/22 18:19:30 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define	FDF_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "stdbool.h"
#include <X11/keysym.h>

# define WIDTH 1000
# define HEIGHT 1000

typedef struct s_fdf
{
	void	*mlx;
	void	*img;
	void	*win;

	int		**arr_map;
	int 	**arr_color;
	int 	*pixel_data;
	int 	arr_height;
	int 	arr_width;

	int 	color_from;
	int 	color_to;

	float 	total_len;
	float 	distance_traveled;

	float	map_width;
	float	map_height;

	int		bpp;
	int		size_line;
	int		endian;

	float	offset_x;
	float	offset_y;

	int		max_color;
	int		min_color;

	float 	x;
	float 	y;
	float 	z;
	float 	x1;
	float 	y1;
	float 	z1;

	float 	zoom;
	float 	angle;

	float 	min_x;
	float	max_x;
	float	min_y;
	float	max_y;

	int 	max_z;
	int 	min_z;

}				t_fdf;

// error handling
void	return_error(char *err_message);
void	free_int_arr(int **arr, int count);
int		free_fdf(t_fdf *map);
void	free_split_line(char **split_line, int i);
void	safe_free_line(char *line);

// parse_utils.c
int	map_height(char *file);
int	map_width(char *file);

// parse.c parsing map
int 	count_digits(char *str);
void	parse_file(char *file, t_fdf *map);

// new_fdf.c
int	main(int ac, char **av);

// draw.c
void	draw(t_fdf *map);

// parse_color.c
void	fill_color_arr(char *file, t_fdf *map);
int		calculate_color(int z_value, t_fdf *map);
int		calculate_color_put_pixel(t_fdf *map);

// parse_color_utils.c
int	hex_to_int(const char *hex_str);
int	adjust_red(int min, int max, float ratio);
int	adjust_green(int min, int max, float ratio);
int	adjust_blue(int min, int max, int ratio);

#endif
