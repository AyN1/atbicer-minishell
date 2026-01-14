/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 01:23:08 by aschweit          #+#    #+#             */
/*   Updated: 2026/01/14 01:23:08 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_token_type type)
{
	return (type == type_Redir_in || type == type_Redir_out
		|| type == type_Redir_append || type == type_Redir_app);
}

void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		if (redir->file)
			free(redir->file);
		free(redir);
		redir = tmp;
	}
}

void	free_commands(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds->next;
		free_argv(cmds->argv);
		free_redirs(cmds->redirs);
		free(cmds);
		cmds = tmp;
	}
}

void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

int	count_args(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current && current->type != type_Pipe)
	{
		if (is_redir(current->type))
		{
			current = current->next;
			if (current)
				current = current->next;
			continue ;
		}
		if (current->type == type_Word || current->type == type_Var
			|| current->type == type_Var_exit || current->type == type_Var_pid)
			count++;
		current = current->next;
	}
	return (count);
}
