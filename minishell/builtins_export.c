/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 by aschweit              #+#    #+#                */
/*   Updated: 2026/01/13 by aschweit                 ###   ########.fr       */
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

int	builtin_export(char **argv, char **envp)
{
	int		i;
	char	*name;
	char	*value;

	if (!argv[1])
	{
		print_export_env(envp);
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		if (!is_valid_var_name(argv[i]))
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		name = get_var_name(argv[i]);
		value = get_var_value(argv[i]);
		if (value)
			setenv(name, value, 1);
		free(name);
		i++;
	}
	return (0);
}
