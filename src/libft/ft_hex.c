/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:20:18 by dbisko            #+#    #+#             */
/*   Updated: 2024/01/08 21:04:23 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	convert_to_lower_hex_char(int digit)
{
	if (digit >= 0 && digit <= 9)
		return (digit + '0');
	else
		return ('a' + (digit - 10));
}

char	convert_to_upper_hex_char(int digit)
{
	if (digit >= 0 && digit <= 9)
		return (digit + '0');
	else
		return ('A' + (digit - 10));
}

int	ft_print_lower_hex(unsigned int num)
{
	int		printed_len;
	char	one_in_hex;

	printed_len = 0;
	if (num > 15)
		printed_len += ft_print_lower_hex(num / 16);
	one_in_hex = convert_to_lower_hex_char(num % 16);
	write(1, &one_in_hex, 1);
	printed_len += 1;
	return (printed_len);
}

int	ft_print_upper_hex(unsigned int num)
{
	int		printed_len;
	char	one_in_hex;

	printed_len = 0;
	if (num > 15)
		printed_len += ft_print_upper_hex(num / 16);
	one_in_hex = convert_to_upper_hex_char(num % 16);
	write(1, &one_in_hex, 1);
	printed_len += 1;
	return (printed_len);
}
