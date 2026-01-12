/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:00:48 by atbicer           #+#    #+#             */
/*   Updated: 2023/08/30 03:23:49 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*needle)
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		while (i + j < len && haystack[i + j] == needle[j])
		{
			if (j == ft_strlen(needle) - 1)
				return ((char *)haystack + i);
			++j;
		}
		j = 0;
		++i;
	}
	return (0);
}
