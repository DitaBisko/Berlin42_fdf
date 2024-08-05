/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:03:44 by dbisko            #+#    #+#             */
/*   Updated: 2024/07/11 18:09:34 by dbisko           ###   ########.fr       */
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
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"

typedef struct s_fdf
{
	void	*mlx;
	void	*img;

	int		**arr_map;
	int 	**arr_color;
	int 	height;
	int 	width;

	float 	zoom;
	float	x;
	float 	y;
	float	x1;
	float	y1;
	float 	z;
	float 	z1;
	float 	angle;

}				t_fdf;

// error handling
void	return_error(char *err_message);
void	free_int_arr(int **arr, int count);

// pars map utils

int 	count_digits(char *str);
void	parse_file(char *file, t_fdf *map);

// fdf.c
int	main(int ac, char **av);

#endif