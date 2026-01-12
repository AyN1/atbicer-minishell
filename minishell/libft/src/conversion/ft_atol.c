/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:24:57 by atbicer           #+#    #+#             */
/*   Updated: 2025/05/13 05:03:56 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* don't handle overflow and underflow as the original. */
long	ft_atol(const char *str)
{
	int		i;
	long	nb;
	int		sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		++i;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		++i;
	while (ft_isdigit(str[i]))
		nb = nb * 10 + (str[i++] - '0');
	return (nb * sign);
}
