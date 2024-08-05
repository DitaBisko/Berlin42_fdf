/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hadle_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:32:34 by dbisko            #+#    #+#             */
/*   Updated: 2024/08/01 14:32:34 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	handle_input(int key_code, t_fdf *map)
{
	if (key_code == KEY_ESC)
	{
		mlx_destroy_display(map->mlx);
		mlx_destroy_window(map->mlx);
		free_fdf(map);
		exit(1);
	}

}