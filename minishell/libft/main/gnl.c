/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:53:25 by atbicer           #+#    #+#             */
/*   Updated: 2024/10/11 22:44:32 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#define NBR_EXEC 9

int	main(void)
{
	int fd;
	char *ret;

	fd = open("txt/text.txt", O_RDONLY);
	while (1)
	{
		ret = get_next_line(fd);
		if (!ret)
		{
			//	system("leaks -nocontext a.out | grep -A5 \"malloced\"");
			return (-1);
		}
		printf("%s", ret);
	}
	return (0);
}
