/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 03:03:08 by atbicer           #+#    #+#             */
/*   Updated: 2023/08/30 01:30:32 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	total_len;

	dst_len = ft_strlen(dst);
	if (dstsize > dst_len)
	{
		total_len = dstsize - dst_len;
		ft_strlcpy(dst + dst_len, src, total_len);
		return (ft_strlen(src) + dst_len);
	}
	return (ft_strlen(src) + dstsize);
}
