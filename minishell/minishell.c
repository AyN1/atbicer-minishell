/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:31:13 by aschweit       #+#    #+#                */
/*   Updated: 2026/01/13 by aschweit                 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

struct termios	g_original_term;

void	setup_terminal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &g_original_term);
	term = g_original_term;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	restore_terminal(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_original_term);
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	process_line(char *line_input, char **envp)
{
	t_token	*tokens;
	t_cmd	*cmds;

	add_history(line_input);
	tokens = tokenize_with_quotes(line_input);
	cmds = parse(tokens);
	if (cmds)
		execute_cmds(cmds, envp);
	free_tokens(tokens);
	free_commands(cmds);
}

static int	handle_input(char *line_input, char **envp)
{
	if (!line_input)
	{
		printf("exit\n");
		return (1);
	}
	if (!*line_input)
	{
		free(line_input);
		return (0);
	}
	if (ft_strncmp(line_input, "exit", 4) == 0)
	{
		free(line_input);
		return (1);
	}
	process_line(line_input, envp);
	free(line_input);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line_input;
	int		end;

	(void)argc;
	(void)argv;
	end = 0;
	setup_terminal();
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (!end)
	{
		line_input = readline("minishell> ");
		end = handle_input(line_input, envp);
	}
	restore_terminal();
	rl_clear_history();
	return (0);
}
