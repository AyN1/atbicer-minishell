/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 23:50:35 by atbicer           #+#    #+#             */
/*   Updated: 2023/08/30 00:54:07 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s1);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len + 1);
	return (str);
}
