/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_more.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:37:22 by dbisko            #+#    #+#             */
/*   Updated: 2024/08/15 18:37:24 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	invalid_file_err(char *message)
{
	ft_printf("%s", message);
	exit (1);
}

void	empty_file(char *message, t_fdf *map)
{
	free(map);
	ft_printf("%s", message);
	exit (1);
}

void	file_validity(char *file)
{
	char	buffer[1];
	int		bytes_read;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1) 
		invalid_file_err("Error: Incorect file: non-existant / no permision\n");
	bytes_read = read(fd, buffer, 1);
	if (bytes_read == -1) 
	{
		close(fd);
		invalid_file_err("Error: read error\n");
	}
	else if (bytes_read == 0)
	{
		close(fd);
		invalid_file_err("Error: empty file\n");
	}
	close(fd);
}
