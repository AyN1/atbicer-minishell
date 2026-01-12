/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_digit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:01:37 by atbicer           #+#    #+#             */
/*   Updated: 2024/06/26 13:39:38 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_digit(long n, int base, char specifier)
{
	int		count;
	char	*symbols;
	char	*cap_sym;

	symbols = "0123456789abcdef";
	cap_sym = "0123456789ABCDEF";
	count = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		return (ft_print_digit(-n, base, specifier) + 1);
	}
	else if (n < base)
	{
		if (specifier == 'x')
			return (ft_print_char(symbols[n]));
		else
			return (ft_print_char(cap_sym[n]));
	}
	else
	{
		count = ft_print_digit(n / base, base, specifier);
		return (count + ft_print_digit(n % base, base, specifier));
	}
}
