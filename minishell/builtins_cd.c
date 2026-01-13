/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 by aschweit              #+#    #+#                */
/*   Updated: 2026/01/13 by aschweit                 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_pwd_vars(char *old_pwd)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
		setenv("PWD", cwd, 1);
	if (old_pwd)
		setenv("OLDPWD", old_pwd, 1);
}

int	builtin_cd(char **argv)
{
	char	old_pwd[4096];
	char	*path;

	if (!getcwd(old_pwd, sizeof(old_pwd)))
		old_pwd[0] = '\0';
	if (!argv[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
	}
	else
		path = argv[1];
	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (1);
	}
	update_pwd_vars(old_pwd);
	return (0);
}
