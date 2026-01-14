/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 01:12:18 by atbicer           #+#    #+#             */
/*   Updated: 2026/01/14 01:12:27 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	exit_with_error(char *arg)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(2);
}

static void	exit_with_code(char **argv)
{
	int	exit_code;

	exit_code = ft_atoi(argv[1]);
	if (argv[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return ;
	}
	exit(exit_code % 256);
}

int	builtin_exit(char **argv)
{
	ft_putstr_fd("exit\n", 1);
	if (!argv[1])
		exit(0);
	if (is_numeric(argv[1]))
		exit_with_code(argv);
	else
		exit_with_error(argv[1]);
	return (1);
}
