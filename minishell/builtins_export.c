/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 01:09:58 by atbicer           #+#    #+#             */
/*   Updated: 2026/01/14 01:12:05 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export_env(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(envp[i], 1);
		write(1, "\n", 1);
		i++;
	}
}

static int	is_valid_var_name(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!(str[0] == '_' || ft_isalpha(str[0])))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(str[i] == '_' || ft_isalnum(str[i])))
			return (0);
		i++;
	}
	return (1);
}

static char	*get_var_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = malloc(i + 1);
	if (!name)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

static char	*get_var_value(char *str)
{
	char	*equals;

	equals = ft_strchr(str, '=');
	if (!equals)
		return (NULL);
	return (equals + 1);
}

static int	export_var(char *arg)
{
	char	*name;
	char	*value;

	if (!is_valid_var_name(arg))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	name = get_var_name(arg);
	value = get_var_value(arg);
	if (value)
		setenv(name, value, 1);
	free(name);
	return (0);
}

int	builtin_export(char **argv, char **envp)
{
	int		i;
	int		ret;

	if (!argv[1])
	{
		print_export_env(envp);
		return (0);
	}
	i = 1;
	ret = 0;
	while (argv[i])
	{
		if (export_var(argv[i]))
			ret = 1;
		i++;
	}
	return (ret);
}
