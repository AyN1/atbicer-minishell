#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

#define TEST1 "Ello Govn'a %s\n", "ATBICER"
#define TEST2 "The magic number is %d in hex %x in caps hex %X\n", 42, 42, 42
#define TEST3 "%x %x %x %x %x %x %x %x %x %x - %x %x %x %x %x - %x %x %x %x %x\n", 42, 42, 42, 42, 42,    42, 42, 42, 42, 42,    42, 42, 42, 42, 42,   42, 42, 42, 42, 42

void	ft_len_check(int *ret, int *ft_ret)
{
	if (*ret != *ft_ret)
	{
		printf("KO!\texpected:[%d] yours:[%d]\n\n", *ret, *ft_ret);
		exit(1);
	}
	else
		printf("Ok :D\texpected:[%d] yours:[%d]\n\n", *ret, *ft_ret);
	*ret = 0;
	*ft_ret = 0;
}

int	main(void)
{
	int	ret;
	int	ft_ret;

	ret = 0;
	ft_ret = 0;
	ret = printf(TEST1);
	ft_ret = ft_printf(TEST1);
	ft_len_check(&ret, &ft_ret);
	
	ret = printf(TEST2);
	ft_ret = ft_printf(TEST2);
	ft_len_check(&ret, &ft_ret);
	
	ret = printf(TEST3);
	ft_ret = ft_printf(TEST3);
	ft_len_check(&ret, &ft_ret);
	return (0);
}
