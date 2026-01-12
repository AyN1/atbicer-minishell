/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:32:50 by atbicer           #+#    #+#             */
/*   Updated: 2025/05/21 09:22:02 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_addr(unsigned long long n)
{
	char	*symbols;
	int		count;

	symbols = "0123456789abcdef";
	count = 0;
	if (n < 16)
		return (ft_print_char(symbols[n]));
	else
	{
		count = ft_put_addr(n / 16);
		return (count + ft_put_addr(n % 16));
	}
}

int	ft_print_ptr(unsigned long long ptr)
{
	int	count;

	count = 0;
	count += write(1, "0x", 2);
	if (!ptr)
		count += write(1, "0", 1);
	else
		count += ft_put_addr(ptr);
	return (count);
}
