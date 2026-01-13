/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 23:02:40 by atbicer           #+#    #+#             */
/*   Updated: 2026/01/13 22:21:47 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <errno.h>

/* ---------- small utils ---------- */


static char	*ft_strjoin3(const char *a, const char *b, const char *c)
{
	size_t la = ft_strlen(a);
	size_t lb = ft_strlen(b);
	size_t lc = ft_strlen(c);
	char *out = malloc(la + lb + lc + 1);
	size_t i = 0;

	if (!out)
		return (NULL);
	while (a && *a) out[i++] = *a++;
	while (b && *b) out[i++] = *b++;
	while (c && *c) out[i++] = *c++;
	out[i] = '\0';
	return (out);
}

/* split PATH by ':' */
static char	**split_colon(const char *s)
{
	int count = 1;
	int i = 0, j = 0, start = 0;
	char **arr;

	if (!s)
		return (NULL);
	while (s[i])
		if (s[i++] == ':')
			count++;
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (1)
	{
		if (s[i] == ':' || s[i] == '\0')
		{
			int len = i - start;
			arr[j] = malloc(len + 1);
			if (!arr[j])
				return (NULL); /* (simple v0: not handling partial free) */
			for (int k = 0; k < len; k++)
				arr[j][k] = s[start + k];
			arr[j][len] = '\0';
			j++;
			if (s[i] == '\0')
				break;
			start = i + 1;
		}
		i++;
	}
	arr[j] = NULL;
	return (arr);
}

static void	free_split(char **arr)
{
	int i = 0;
	if (!arr) return;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

/* find executable path using PATH */
static char	*resolve_path(char *cmd, char **envp)
{
	char *path_env;
	char **paths;
	char *full;
	int i;

	if (!cmd || !*cmd)
		return (NULL);
	/* if contains '/', try direct */
	for (i = 0; cmd[i]; i++) // replace it with a while loop.
		if (cmd[i] == '/')
			return (strdup(cmd));
	(void)envp;
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	paths = split_colon(path_env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full = ft_strjoin3(paths[i], "/", cmd);
		if (full && access(full, X_OK) == 0)
		{
			free_split(paths);
			return (full);
		}
		free(full);
		i++;
	}
	free_split(paths);
	return (NULL);
}

static int	is_builtin(char *cmd)
{
	if (!ft_strcmp("echo", cmd))
		return (1);
	if (!ft_strcmp("pwd", cmd))
		return (1);
	if (!ft_strcmp("cd", cmd))
		return (1);
	if (!ft_strcmp("env", cmd))
		return (1);
	if (!ft_strcmp("export", cmd))
		return (1);
	if (!ft_strcmp("unset", cmd))
		return (1);
	if (!ft_strcmp("exit", cmd))
		return (1);
	return (0);
}

static int	run_builtin(char **argv)
{
	if (!ft_strcmp("echo", argv[0]))
		return (builtin_echo(argv));
	if (!ft_strcmp("pwd", argv[0]))
		return (builtin_pwd());
	else
	{
		write(2, "minishell: ", 11);
		write(2, argv[0], ft_strlen(argv[0]));
		write(2, ": not implemented\n", 18);
		return (1);
	}
}

/* ---------- public entry ---------- */

int	execute_cmds(t_cmd *cmds, char **envp)
{
	pid_t pid;
	int status;
	char *path;

	if (!cmds || !cmds->argv || !cmds->argv[0])
		return (0);

	/* v0: ignore pipes and redirs */
	if (cmds->next || cmds->redirs)
	{
		write(2, "v0: pipes/redirs not implemented yet\n", 38);
		return (1);
	}

	/* builtin in parent (good enough for echo test) */
	if (is_builtin(cmds->argv[0]))
		return (run_builtin(cmds->argv));

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		path = resolve_path(cmds->argv[0], envp);
		if (!path)
		{
			write(2, "minishell: command not found: ", 30);
			write(2, cmds->argv[0], ft_strlen(cmds->argv[0]));
			write(2, "\n", 1);
			exit(127);
		}
		execve(path, cmds->argv, envp);
		perror("execve");
		exit(126);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
