/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:31:05 by dbisko            #+#    #+#             */
/*   Updated: 2024/07/31 20:54:57 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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
	*y = (temp + *y) * sin(map->angle) - (z * map->z_scale);
}

void	set_min_max_coordinates(t_fdf *map)
{
	map->min_x = 1e30;
	map->max_x = -1e30;
	map->min_y = 1e30;
	map->max_y = -1e30;
}
