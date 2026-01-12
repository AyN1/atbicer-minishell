/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 21:03:02 by atbicer           #+#    #+#             */
/*   Updated: 2025/05/03 15:14:33 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
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
		nb = nb * 10 + (str[i++] - 48);
	return (nb * sign);
}
