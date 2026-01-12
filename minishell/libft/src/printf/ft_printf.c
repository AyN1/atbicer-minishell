/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:25:35 by atbicer           #+#    #+#             */
/*   Updated: 2024/06/26 16:15:09 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_char(int c)
{
	return (write(1, &c, 1));
}

int	print_format(char specifier, va_list ap)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count = ft_print_char(va_arg(ap, int));
	else if (specifier == 's')
		count = ft_print_str(va_arg(ap, char *));
	else if (specifier == 'p')
		count = ft_print_ptr(va_arg(ap, unsigned long long));
	else if (specifier == 'd' || specifier == 'i')
		count = ft_print_digit((long)va_arg(ap, int), 10, specifier);
	else if (specifier == 'u')
		count = ft_print_digit((long)va_arg(ap, unsigned int), 10, specifier);
	else if (specifier == 'x' || specifier == 'X')
		count = ft_print_digit((long)va_arg(ap, unsigned int), 16, specifier);
	else
		count += write(1, &specifier, 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, format);
	count = 0;
	while (*format != 0)
	{
		if (*format == '%')
			count += print_format(*(++format), ap);
		else
			count += write(1, format, 1);
		++format;
	}
	va_end(ap);
	return (count);
}
