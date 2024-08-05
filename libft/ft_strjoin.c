/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:27:23 by dbisko            #+#    #+#             */
/*   Updated: 2023/11/29 10:27:54 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char			*joined_s;
	unsigned int	joined_index;
	unsigned int	string_index;

	joined_s = (char *)malloc((ft_strlen(s1)
							   + ft_strlen(s2) + 1) * sizeof(char));
	if (!joined_s)
		return (NULL);
	joined_index = 0;
	string_index = 0;
	while (s1[string_index])
		joined_s[joined_index++] = s1[string_index++];
	string_index = 0;
	while (s2[string_index])
		joined_s[joined_index++] = s2[string_index++];
	joined_s[joined_index] = '\0';
	return (joined_s);
}
