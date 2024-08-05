/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 17:26:05 by dbisko            #+#    #+#             */
/*   Updated: 2024/01/08 21:09:25 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	num_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

void	put_num(unsigned int n)
{
	char	number;

	if (n > 9)
		put_num(n / 10);
	number = (n % 10) + '0';
	write (1, &number, 1);
}

int	ft_print_number(int number)
{
	int	len_printed;

	len_printed = 0;
	if (number == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (number < 0)
	{
		write(1, "-", 1);
		number = -number;
		len_printed += 1;
	}
	len_printed += num_len(number);
	put_num(number);
	return (len_printed);
}

int	ft_print_unsigned(unsigned int n)
{
	int	len_printed;

	len_printed = 0;
	if (n == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	len_printed += num_len(n);
	put_num(n);
	return (len_printed);
}
