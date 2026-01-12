/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 04:48:31 by atbicer           #+#    #+#             */
/*   Updated: 2023/08/28 17:59:39 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	c = (unsigned char)c;
	if (!c)
		return ((char *)&s[len]);
	while (len--)
	{
		if (s[len] == c)
			return ((char *)&s[len]);
	}
	return (NULL);
}
