/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:42:51 by atbicer           #+#    #+#             */
/*   Updated: 2023/09/03 04:06:21 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DISPLAY_TEST 0
#define DISPLAY_FAILED_TEST 1

int	ft_test_1(int (*f)(int), int (*ft)(int), int c)
{
	int	ret;
	int	ft_ret;

	ret = f(c);
	ft_ret = ft(c);
	if (DISPLAY_TEST)
	{
		printf("original(%c) ret(%d)\n", c, ret);
		printf("ft(%c) ret(%d)\n", c, ft_ret);
	}
	if (ret == ft_ret)
		return (1);
	else
	{
		if (DISPLAY_FAILED_TEST)
		{
			printf("libc:\t(%c) ret(%d)\n", c, ret);
			printf("ft:\t(%c) ret(%d)\n", c, ft_ret);
		}
		return (-1);
	}
}

void	ft_batch_test_1(int (*f)(int), int (*ft)(int), const char *str)
{
	int	i;

	printf("---%s TEST---\n", str);
	i = -1;
	while (++i <= 127)
	{
		if (ft_test_1(f, ft, i) != 1)
		{
			printf("Failure\n\n");
			return ;
		}
	}
	printf("Success\n\n");
}

char	*generate_random_string(size_t length)
{
	char	*random_string;
	int		key;

	const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	random_string = NULL;
	if (length)
	{
		random_string = malloc(sizeof(char) * (length + 1));
		if (random_string)
		{
			for (size_t n = 0; n < length; n++)
			{
				key = rand() % (sizeof(charset) - 1);
				random_string[n] = charset[key];
			}
			random_string[length] = '\0';
		}
	}
	return (random_string);
}

void	ft_test_strlen(int num_iterations)
{
	char	*random_str;
	size_t	original_len;
	size_t	custom_len;
	size_t	random_length;
	int		failure;

	failure = 0;
	printf("---FT_STRLEN TEST---\n");
	srand(time(NULL)); // Seed for random number generation
	for (int i = 0; i < num_iterations; i++)
	{
		random_length = rand() % 50;
		// Generate random length for the string
		random_str = generate_random_string(random_length);
		if (random_str)
		{
			// printf("Testing string: %s\n", random_str);
			original_len = strlen(random_str);
			custom_len = ft_strlen(random_str);
			if (original_len == custom_len)
				; // printf("Match! Length: %zu\n\n", original_len);
			else
			{
				failure = 1;
				printf("Mismatch! Original: %zu, Custom: %zu\n\n", original_len,
					custom_len);
			}
			free(random_str);
		}
	}
	if (strlen("") != ft_strlen(""))
		printf("Emtpy string test failed\n\n");
	if (!failure)
		printf("Success\n\n");
	else
		printf("Random string failures\n\n");
}

void	ft_test_memset(int c, size_t len)
{
	char	b[len];
	char	ft_b[len];
	char	*ret;
	char	*ft_ret;
	size_t	i;

	printf("---FT_MEMSET TEST---\n");
	ret = (char *)memset(b, c, len);
	ft_ret = (char *)ft_memset(ft_b, c, len);
	i = 0;
	while (i < len)
	{
		if (ret[i] != ft_ret[i])
		{
			printf("Failure\n");
			if (DISPLAY_FAILED_TEST)
			{
				printf("ret memset: %p - %s\n", ret, (char *)ret);
				printf("ret ft_memset: %p - %s\n", ft_ret, (char *)ft_ret);
			}
			return ;
		}
		++i;
	}
	printf("Success\n\n");
}

int	ft_test_bzero(size_t n)
{
	char buffer1[100] = "abcdefghi";
	char buffer2[100] = "abcdefghi";
	printf("---FT_BZERO TEST---\n");
	ft_bzero(buffer1 + 2, n);
	bzero(buffer2 + 2, n);
	if (DISPLAY_TEST)
	{
		printf("Buffer after ft_bzero: %s\n", buffer1);
		printf("Buffer after bzero: %s\n", buffer2);
	}
	for (int i = 0; i < 10; i++)
	{
		if (buffer1[i] != buffer2[i])
		{
			printf("Failure: Mismatch at position %d: ft_bzero=%d, bzero=%d\n",
				i, buffer1[i], buffer2[i]);
			return (1);
		}
	}
	printf("Success\n\n");
	return (0);
}

int	ft_test_memcpy(size_t n)
{
	char	*ret1;
	char	*ret2;

	char buffer1[100] = "abcdefghi";
	char buffer2[100] = "abcdefghi";
	ret1 = memcpy(buffer1, "Hello", n);
	ret2 = (char *)ft_memcpy(buffer2, "Hello", n);
	if (DISPLAY_TEST)
	{
		printf("libc:\t%s %s\n", ret1, buffer1);
		printf("ft:\t%s %s\n", ret2, buffer2);
	}
	for (int i = 0; i < 10; i++)
	{
		if (buffer1[i] != buffer2[i])
		{
			if (DISPLAY_FAILED_TEST)
			{
				printf("%s %s\n", ret1, buffer1);
				printf("%s %s\n", ret2, buffer2);
			}
			printf("Failure");
			return (1);
		}
	}
	return (0);
}

int	ft_batch_test_memcpy(size_t iteration)
{
	size_t	i;

	i = 0;
	printf("---FT_MEMCPY TEST---\n");
	while (i < iteration)
	{
		if (ft_test_memcpy(i) != 0)
		{
			printf("Failure\n");
			return (-1);
		}
		i++;
	}
	printf("Success !\n\n");
	return (0);
}

int	ft_test_memmove(size_t n)
{
	char	*ret;
	char	*ft_ret;

	char data1[] = "Hello, World!";
	char data2[] = "Hello, World!";
	ret = memmove(data1 + 5, data1, n);
	ft_ret = ft_memmove(data2 + 5, data2, n);
	if (DISPLAY_TEST)
	{
		printf("libc:\t[%s] ret:[%s]\n", data1, ret);
		printf("ft:\t[%s] ret:[%s]\n\n", data2, ft_ret);
	}
	if (strcmp(data1, data2) != 0)
	{
		if (DISPLAY_FAILED_TEST)
		{
			printf("libc:\t[%s] ret:[%s]\n", data1, ret);
			printf("ft:\t[%s] ret:[%s]\n\n", data2, ft_ret);
		}
		return (-1);
	}
	if (strcmp(ret, ft_ret) != 0)
	{
		if (DISPLAY_FAILED_TEST)
		{
			printf("libc:\t[%s] ret:[%s]\n", data1, ret);
			printf("ft:\t[%s] ret:[%s]\n\n", data2, ft_ret);
		}
		return (-1);
	}
	return (0);
}
int	ft_batch_test_memmove(size_t iteration)
{
	size_t	i;

	i = 0;
	printf("---FT_STRMEMMOVE TEST---\n");
	while (i < iteration)
	{
		if (ft_test_memmove(i) != 0)
		{
			printf("Failure\n");
			return (-1);
		}
		i++;
	}
	printf("Success !\n\n");
	return (0);
}

int	ft_test_strlcpy(void)
{
	char	dest1[256];
	char	dest2[256];

	char src[] = "Test string";
	size_t result1, result2;
	printf("---FT_STRLCPY TEST---\n");
	result1 = ft_strlcpy(dest1, src, sizeof(dest1));
	result2 = strlcpy(dest2, src, sizeof(dest2));
	if (strcmp(dest1, dest2) != 0 || result1 != result2)
	{
		printf("ft_strlcpy Test 1 failed!\n");
		return (0);
	}
	// Test 2: Limited copy
	result1 = ft_strlcpy(dest1, src, 5);
	result2 = strlcpy(dest2, src, 5);
	if (strcmp(dest1, dest2) != 0 || result1 != result2)
	{
		printf("ft_strlcpy Test 2 failed!\n");
		return (0);
	}
	// Test 3: 0 size
	result1 = ft_strlcpy(dest1, "aaa", 0);
	result2 = strlcpy(dest2, "aaa", 0);
	if (strcmp(dest1, dest2) != 0 || result1 != result2)
	{
		printf("ft_strlcpy Test 1 failed!\n");
		return (0);
	}
	// You can add more tests as needed...
	printf("ft_strlcpy passed all tests.\n\n");
	return (1);
}

int	ft_test_strlcat(size_t size)
{
	char	*src;
	int		ret;
	int		ft_ret;

	char dest[256] = "Hello";
	char ft_dest[256] = "Hello";
	src = "World";
	ret = strlcat(dest, src, size);
	ft_ret = ft_strlcat(ft_dest, src, size);
	if (DISPLAY_TEST)
	{
		printf("libc:\t%s (%d)\n", dest, ret);
		printf("ft:\t%s (%d)\n", ft_dest, ft_ret);
	}
	if (strcmp(dest, ft_dest) != 0)
	{
		if (DISPLAY_FAILED_TEST)
		{
			printf("libc:\t%s (%d)\n", dest, ret);
			printf("ft:\t%s (%d)\n", ft_dest, ft_ret);
		}
		return (-1);
	}
	if (ret != ft_ret)
	{
		if (DISPLAY_FAILED_TEST)
		{
			printf("libc:\t%s (%d)\n", dest, ret);
			printf("ft:\t%s (%d)\n", ft_dest, ft_ret);
		}
		return (-1);
	}
	return (0);
}

int	ft_batch_test_strlcat(size_t iteration)
{
	size_t	i;

	i = 0;
	printf("---FT_STRLCAT TEST---\n");
	while (i < iteration)
	{
		if (ft_test_strlcat(i) != 0)
		{
			printf("Failure\n");
			return (-1);
		}
		i++;
	}
	printf("Success !\n\n");
	return (0);
}

int	ft_test_strchr(void)
{
	char buff[] = "tripouille";
	printf("---FT_STRCHR TEST---\n");
	printf("libc: \t[%s]\n", strchr(buff, 't' + 256));
	printf("ft:\t[%s]\n\n", ft_strchr(buff, 't' + 256));
	return (0);
}

int	ft_test_strrchr(void)
{
	char buff[] = "bonjour";
	printf("---FT_STRRCHR TEST---\n");
	printf("libc: \t[%s]\n", strrchr(buff, 0));
	printf("ft:\t[%s]\n\n", ft_strrchr(buff, 0));
	return (0);
}

int	ft_test_memcmp(const void *s1, const void *s2, size_t iteration)
{
	int		ret;
	int		ft_ret;
	size_t	i;

	i = 0;
	while (i < iteration)
	{
		ret = memcmp(s1, s2, i);
		ft_ret = ft_memcmp(s1, s2, i);
		if (DISPLAY_TEST)
		{
			printf("libc:\t[%d]\n", ret);
			printf("ft:\t[%d]\n", ft_ret);
		}
		if (ret != ft_ret)
		{
			if (DISPLAY_FAILED_TEST)
			{
				printf("libc:\t[%d]\n", ret);
				printf("ft:\t[%d]\n", ft_ret);
			}
			return (-1);
		}
		++i;
	}
	return (0);
}

int	ft_batch_test_memcmp(size_t iteration)
{
	printf("---FT_MEMCMP TEST---\n");
	if ((ft_test_memcmp("test", "test", iteration)) != 0)
		return (printf("Failure\n"));
	if ((ft_test_memcmp("lina", "linaz", iteration)) != 0)
		return (printf("Failure\n"));
	if ((ft_test_memcmp("abcde", "abcdef", iteration)) != 0)
		return (printf("Failure\n"));
	if ((ft_test_memcmp("123123123", "123123123f", iteration)) != 0)
		return (printf("Failure\n"));
	printf("Succes\n\n");
	return (0);
}

int	ft_test_strnstr(char *s1, char *s2, size_t size)
{
	char	*ret;
	char	*ft_ret;
	int		diff;

	while (size--)
	{
		ret = strnstr(s1, s2, size);
		ft_ret = ft_strnstr(s1, s2, size);
		if (!(!ret || !ft_ret))
			diff = strcmp(ret, ft_ret);
		if (diff)
		{
			if (DISPLAY_FAILED_TEST)
			{
				printf("test: [%s] [%s] [%zu]\n", s1, s2, size);
				printf("libc:\t[%s]\n", ret);
				printf("ft:\t[%s]\n", ft_ret);
			}
			return (-1);
		}
	}
	return (0);
}

int	ft_batch_test_strnstr(void)
{
	printf("---FT_STRNSTR TEST---\n");
	if ((ft_test_strnstr("lorem", "rem", 13)) != 0)
		return (printf("Failure\n"));
	if ((ft_test_strnstr("aaabaaaa", "aaaa", 13)) != 0)
		return (printf("Failure\n"));
	printf("Succes\n\n");
	return (0);
}

int	main(void)
{
	ft_batch_test_1(isalpha, ft_isalpha, "FT_ISALPHA");
	ft_batch_test_1(isdigit, ft_isdigit, "FT_ISDIGIT");
	ft_batch_test_1(isalnum, ft_isalnum, "FT_ISALNUM");
	ft_batch_test_1(isascii, ft_isascii, "FT_ISASCII");
	ft_batch_test_1(isprint, ft_isprint, "FT_ISPRINT");
	ft_test_strlen(900);
	ft_test_memset(97, 0);
	ft_test_bzero(5);
	ft_batch_test_memcpy(10);
	ft_batch_test_memmove(10);
	ft_test_strlcpy();
	ft_batch_test_strlcat(15);
	ft_batch_test_1(toupper, ft_toupper, "FT_TOUPPER");
	ft_batch_test_1(tolower, ft_tolower, "FT_TOLOWER");
	ft_test_strchr();
	ft_test_strrchr();
	ft_batch_test_memcmp(10);
	ft_batch_test_strnstr();
	return (0);
}
