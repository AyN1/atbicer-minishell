/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 00:45:35 by atbicer           #+#    #+#             */
/*   Updated: 2025/05/13 05:02:13 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (!join)
		return (NULL);
	ft_strlcpy(join, (char *)s1, s1_len + 1);
	ft_strlcpy(join + s1_len, (char *)s2, s2_len + 1);
	return (join);
}
