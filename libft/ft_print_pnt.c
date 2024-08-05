/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pnt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:59:17 by dbisko            #+#    #+#             */
/*   Updated: 2024/01/11 20:36:38 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	convert_to_hex_char(int digit)
{
	if (digit >= 0 && digit <= 9)
		return (digit + '0');
	else
		return ('a' + (digit - 10));
}

int	print_hex_address(unsigned long digit)
{
	int		printed_len;
	char	one_in_hex;

	printed_len = 0;
	if (digit > 15)
		printed_len += print_hex_address(digit / 16);
	one_in_hex = convert_to_hex_char(digit % 16);
	write(1, &one_in_hex, 1);
	printed_len += 1;
	return (printed_len);
}

int	ft_print_pnt(void *address)
{
	int				printed_len;
	unsigned long	address_to_print;

	printed_len = 0;
	if (address == 0)
	{
		write(1, "(nil)", 5);
		printed_len = 5;
		return (printed_len);
	}
	address_to_print = (unsigned long)address;
	write(1, "0x", 2);
	printed_len += 2;
	printed_len += print_hex_address(address_to_print);
	return (printed_len);
}
