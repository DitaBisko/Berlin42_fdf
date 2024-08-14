/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 23:55:49 by dbisko            #+#    #+#             */
/*   Updated: 2024/01/08 21:28:07 by dbisko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_char(int c)
{
	return (write(1, &c, 1));
}

int	ft_format(char format_specifier, va_list *args)
{
	int	len;

	len = 0;
	if (format_specifier == '%')
		len += ft_put_char(format_specifier);
	else if (format_specifier == 'c')
		len += ft_put_char(va_arg(*args, int));
	else if (format_specifier == 's')
		len += ft_print_str(va_arg(*args, char *));
	else if (format_specifier == 'i' || format_specifier == 'd')
		len += ft_print_number(va_arg(*args, int));
	else if (format_specifier == 'u')
		len += ft_print_unsigned(va_arg(*args, unsigned int));
	else if (format_specifier == 'p')
		len += ft_print_pnt(va_arg(*args, void *));
	else if (format_specifier == 'x')
		len += ft_print_lower_hex(va_arg(*args, int));
	else if (format_specifier == 'X')
		len += ft_print_upper_hex(va_arg(*args, int));
	return (len);
}

int	ft_printf(const char *string, ...)
{
	va_list	args;
	int		index;
	int		printed;

	index = 0;
	printed = 0;
	va_start(args, string);
	while (string[index])
	{
		if (string[index] == '%')
		{
			printed += ft_format(string[index + 1], &args);
			index++;
		}
		else
		{
			write(1, &string[index], 1);
			printed++;
		}
		index++;
	}
	va_end(args);
	return (printed);
}
