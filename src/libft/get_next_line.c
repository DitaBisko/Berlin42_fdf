/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:02:42 by dbisko            #+#    #+#             */
/*   Updated: 2024/01/19 09:06:19 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*join_or_duplicate(char *stash, char *buffer)
{
	char	*result;

	if (stash)
		result = ft_strjoin(stash, buffer);
	else
		result = ft_strdup(buffer);
	return (result);
}

char	*extract_line(char **stash)
{
	char	*line;
	char	*newline;
	char	*new_stash;
	int		line_len;

	line = NULL;
	newline = ft_strchr(*stash, '\n');
	if (newline)
	{
		line_len = newline - *stash + 1;
		line = ft_substr(*stash, 0, line_len);
		new_stash = ft_strdup(newline + 1);
		free(*stash);
		*stash = new_stash;
	}
	else if (*stash && **stash)
	{
		line = ft_strdup(*stash);
		free(*stash);
		*stash = NULL;
	}
	return (line);
}

int	read_to_stash(int fd, char **stash)
{
	char	*buffer;
	ssize_t	bytes_read;
	char	*temp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = join_or_duplicate(*stash, buffer);
		free(*stash);
		*stash = temp;
		if (ft_strchr(buffer, '\n'))
		{
			free(buffer);
			return (1);
		}
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (bytes_read < 0)
		return (-1);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	ssize_t		read_status;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	read_status = read_to_stash(fd, &stash);
	if (read_status < 0 || (read_status == 0 && (!stash || !*stash)))
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	return (extract_line(&stash));
}
