/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:34:56 by dbisko            #+#    #+#             */
/*   Updated: 2024/06/29 21:34:56 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_arr(char **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	count_words(char *str, char sep)
{
	int	result;
	int	in_word;

	result = 0;
	in_word = 0;
	while (*str)
	{
		if (*str == sep)
			in_word = 0;
		else
		{
			if (in_word == 0)
			{
				result++;
				in_word = 1;
			}
		}
		str++;
	}
	return (result);
}

int	word_len(char *str, char sep)
{
	int	len;

	len = 0;
	while (*str && *str != sep)
	{
		len++;
		str++;
	}
	return (len);
}

int	place_words(char **arr, char *str, char sep, int wc)
{
	int	count;
	int	w_len;
	int	word_i;

	count = 0;
	while (count < wc)
	{
		word_i = 0;
		w_len = 0;
		w_len = word_len(str, sep);
		arr[count] = malloc((w_len +1) * sizeof (char));
		if (arr[count] == NULL)
		{
			free_arr(arr, count);
			return (1);
		}
		while (word_i < w_len && *str)
			arr[count][word_i++] = *str++;
		arr[count][word_i] = '\0';
		count++;
		while (*str == sep)
			str++;
	}
	arr[count] = NULL;
	return (0);
}

char	**ft_split(char *str, char sep)
{
	int		word_count;
	char	**str_arr;

	while (*str == sep && *str != '\0')
		str++;
	word_count = count_words(str, sep);
	str_arr = malloc ((word_count + 1) * sizeof (char *));
	if (str_arr == NULL)
		return (NULL);
	if (place_words(str_arr, str, sep, word_count) == 1)
		return (NULL);
	return (str_arr);
}
