/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:31:13 by aschweit          #+#    #+#             */
/*   Updated: 2026/01/14 01:21:54 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_partial_argv(char **argv, int count)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (i < count)
		free(argv[i++]);
	free(argv);
}

static int	handle_token(t_token **current, t_cmd *cmd, char **argv, int *i)
{
	if (is_redir((*current)->type))
	{
		if (!process_redir(current, cmd))
			return (0);
	}
	else
	{
		add_word(*current, argv, i);
		*current = (*current)->next;
	}
	return (1);
}

char	**build_argv(t_token **tokens, t_cmd *cmd)
{
	char	**argv;
	int		count;
	int		i;
	t_token	*current;

	count = count_args(*tokens);
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	current = *tokens;
	while (current && current->type != type_Pipe)
	{
		if (!handle_token(&current, cmd, argv, &i))
			return (free_partial_argv(argv, i), NULL);
	}
	argv[i] = NULL;
	*tokens = current;
	return (argv);
}

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*parse(t_token *tokens)
{
	t_cmd	*head;
	t_token	*tok;
	t_cmd	*cmd;

	if (!check_syntax(tokens))
		return (NULL);
	head = NULL;
	tok = tokens;
	while (tok)
	{
		cmd = new_cmd();
		if (!cmd)
			return (free_commands(head), NULL);
		cmd->argv = build_argv(&tok, cmd);
		if (!cmd->argv)
			return (free(cmd), free_commands(head), NULL);
		add_cmd(&head, cmd);
		if (tok && tok->type == type_Pipe)
			tok = tok->next;
	}
	return (head);
}
