/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 06:15:55 by atbicer           #+#    #+#             */
/*   Updated: 2023/08/29 05:08:00 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strsplitdup(char const *src, char c)
{
	char	*str;
	int		i;

	if (!src)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != c)
		++i;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != c)
	{
		str[i] = src[i];
		++i;
	}
	str[i] = '\0';
	return (str);
}

static int	ft_count_word(char const *str, char c)
{
	int	count_word;
	int	i;

	if (!str)
		return (0);
	count_word = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			count_word++;
		while (str[i] && str[i] != c)
			++i;
		if (str[i])
			++i;
	}
	return (count_word);
}

static void	*ft_free_all(char **split, int n)
{
	while (n >= 0)
	{
		free(split[n]);
		n--;
	}
	free(split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		n;

	if (!s)
		return (NULL);
	split = malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (!split)
		return (NULL);
	i = 0;
	n = 0;
	while (s[i] && n < ft_count_word(s, c))
	{
		while (s[i] == c)
			++i;
		split[n] = ft_strsplitdup(s + i, c);
		if (!split[n])
			return (ft_free_all(split, n));
		while (s[i] != c && s[i])
			++i;
		++n;
	}
	split[n] = NULL;
	return (split);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	**ret;
// 	int		i;
// 	char	*str;

// 	str = "    Hello This Is   A Test  ";
// 	printf("wc(%d)", ft_count_word(str, ' '));
// 	ret = ft_split(str, ' ');
// 	i = 0;
// 	while (ret[i])
// 		printf("[%s] ", ret[i++]);
// }

/*
** 51: iterate until \0 or C is found
** 53: skip C
*/
