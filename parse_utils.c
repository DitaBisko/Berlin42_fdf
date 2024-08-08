/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:53:18 by dbisko            #+#    #+#             */
/*   Updated: 2024/08/04 11:53:18 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	map_height(char *file)
{
	char	*line;
	int		fd;
	int		count;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return_error("Error: opening file\n");
	line = get_next_line(fd);
	printf("line: %s\n", line);
	while (line != NULL)
	{
		count++;
		safe_free_line(line);
		line = get_next_line(fd);
	}
	safe_free_line(line);
	close(fd);
	return (count);
}

int	map_width(char *file)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return_error("Error: opening file\n");
	line = get_next_line(fd);
	count = count_digits(line);
	while (line)
	{
		safe_free_line(line);
		line = get_next_line(fd);
	}
	safe_free_line(line);
	close(fd);
	return (count);
}
