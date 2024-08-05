/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:42:28 by dbisko            #+#    #+#             */
/*   Updated: 2024/08/04 12:42:28 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	hex_to_int(const char *hex_str)
{
	int	result;

	result = 0;
	while (*hex_str)
	{
		result *= 16;
		if (*hex_str >= '0' && *hex_str <= '9')
			result += *hex_str - '0';
		else if (*hex_str >= 'A' && *hex_str <= 'F')
			result += *hex_str - 'A' + 10;
		else if (*hex_str >= 'a' && *hex_str <= 'f')
			result += *hex_str - 'a' + 10;
		hex_str++;
	}
	return (result);
}

int	adjust_red(int min, int max, float ratio)
{
	int	min_red;
	int	max_red;

	min_red = (min >> 16) & 0xFF;
	max_red = (max >> 16) & 0xFF;
	return ((int)round((float)min_red + ratio * (float)(max_red - min_red)));
}

int	adjust_green(int min, int max, float ratio)
{
	int	min_green;
	int	max_green;

	min_green = ((int)min >> 8) & 0xFF;
	max_green = ((int)max >> 8) & 0xFF;
	return ((int)round((float)min_green + ratio
			* (float)(max_green - min_green)));
}

int	adjust_blue(int min, int max, int ratio)
{
	int	min_blue;
	int	max_blue;

	min_blue = min & 0xFF;
	max_blue = max & 0xFF;
	return ((int)round((float)min_blue + ratio
			* (float)(max_blue - min_blue)));
}
