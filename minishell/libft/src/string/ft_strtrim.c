/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 02:14:19 by atbicer           #+#    #+#             */
/*   Updated: 2023/12/07 19:48:30 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_charset(char c, char const *charset)
{
	int	i;

	if (!charset)
		return (0);
	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		++i;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	i;
	size_t	len;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i] && ft_check_charset(s1[i], set) == 1)
		++i;
	len = ft_strlen(s1);
	while (s1[i] && len > 0 && ft_check_charset(s1[len - 1], set) == 1)
		--len;
	len = len - i;
	trim = ft_calloc(len + 1, sizeof(char));
	if (!trim)
		return (NULL);
	trim = ft_memcpy(trim, s1 + i, len);
	return (trim);
}
/*
int	main(void)
{
	char	*s1;
	char	*s2;
	char	*ret;

	s1 = "+-Hello+-";
	s2 = "+-+++++--+";
	ret = ft_strtrim(s1, "+-");
	if (ret)
		printf("[%s] len(%zu)", ret, ft_strlen(ret));
}
*/
