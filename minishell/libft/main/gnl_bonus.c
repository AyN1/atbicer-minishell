/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:53:27 by atbicer           #+#    #+#             */
/*   Updated: 2024/10/11 22:54:58 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#define NBR_EXEC 9

int	main(void)
{
	int		fd;
	int		fd2;
	char	*ret;
	char	*ret2;

	fd = open("txt/text.txt", O_RDONLY);
	fd2 = open("txt/text2.txt", O_RDONLY);
	while (1)
	{
		ret = get_next_line(fd);
		ret2 = get_next_line(fd2);
		if (!ret && !ret2)
		{
			// system("leaks -nocontext a.out | grep -A5 \"malloced\"");
			return (-1);
		}
		printf("%s", ret);
		printf("%s", ret2);
	}
}
