/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 04:18:15 by atbicer           #+#    #+#             */
/*   Updated: 2023/12/07 19:42:24 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		++i;
	}
}
/*
#include <stdio.h>

void	ft_even_index_to_upper(unsigned int index, char *c)
{
	if (index % 2 == 0)
		*c = ft_toupper(*c); // Convert to uppercase if index is even
}

int	main(void)
{
	char iteri[] = "abcdefg";
	printf("before:\t[%s]\n", iteri);
	ft_striteri(iteri, NULL);
	printf("after:\t[%s]\n", iteri);
}
*/
