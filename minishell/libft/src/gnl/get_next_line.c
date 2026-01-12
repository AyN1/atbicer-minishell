/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 21:11:22 by atbicer           #+#    #+#             */
/*   Updated: 2024/10/11 23:08:04 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_free(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

char	*ft_line(char **str)
{
	char	*line;
	char	*temp;
	size_t	i;

	i = 0;
	while ((*str)[i] != '\n' && (*str)[i] != '\0')
		++i;
	if ((*str)[i] == '\n')
	{
		line = ft_substr(*str, 0, i + 1);
		temp = ft_strdup(&(*str)[i + 1]);
		free(*str);
		*str = temp;
	}
	else if ((*str)[i] == '\0' && i > 0)
	{
		line = ft_strdup(*str);
		free(*str);
		*str = NULL;
	}
	else
		line = NULL;
	return (line);
}

char	*read_and_join(int fd, char *str[])
{
	char	buf[BUFFER_SIZE + 1];
	char	*temp;
	ssize_t	ret;

	if (read(fd, buf, 0) < 0)
		return (ft_free(&str[fd]));
	while (1)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0)
			return (NULL);
		buf[ret] = 0;
		temp = ft_strjoin(str[fd], buf);
		if (!temp)
			return (NULL);
		free(str[fd]);
		str[fd] = temp;
		if (ft_strchr(str[fd], '\n') || ret <= 0)
			break ;
	}
	return (str[fd]);
}

char	*get_next_line(int fd)
{
	static char	*str[OPEN_MAX] = {NULL};

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, " ", 0) < 0)
		return (ft_free(&str[fd]));
	if (!str[fd])
		str[fd] = ft_strdup("");
	if (!str[fd])
		return (NULL);
	str[fd] = read_and_join(fd, str);
	if (!str[fd])
		return (NULL);
	if (str[fd][0] == '\0')
		return (ft_free(&str[fd]));
	return (ft_line(&str[fd]));
}
