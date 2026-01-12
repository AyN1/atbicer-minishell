/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 02:50:47 by atbicer           #+#    #+#             */
/*   Updated: 2023/08/29 03:25:46 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		++len;
	while (n)
	{
		++len;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*itoa;
	size_t			len;
	unsigned int	nbr;

	len = ft_nbrlen(n);
	itoa = ft_calloc(len + 1, sizeof(char));
	if (!itoa)
		return (NULL);
	if (n == 0)
		itoa[0] = '0';
	nbr = n;
	if (n < 0)
	{
		itoa[0] = '-';
		nbr = -n;
	}
	while (nbr)
	{
		itoa[--len] = nbr % 10 + 48;
		nbr /= 10;
	}
	return (itoa);
}

// #include <stdio.h>
// #include <string.h>

// int	main(int argc, char *argv[])
// {
// 	int	av1;

// 	if (argc != 2)
// 		return (1);
// 	av1 = atoi(argv[1]);
// 	printf("nbrlen(%d)\n", ft_nbrlen(av1));
// 	printf("ft_itoa: [%s]\n", ft_itoa(av1));
// }
