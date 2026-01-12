/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:13:28 by atbicer           #+#    #+#             */
/*   Updated: 2024/06/26 13:40:06 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_str(char *str)
{
	int	count;

	count = 0;
	if (!str)
	{
		ft_print_str("(null)");
		return (6);
	}
	while (*str != 0)
	{
		ft_print_char((int)*str);
		++count;
		++str;
	}
	return (count);
}
