/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:31:13 by aschweit       #+#    #+#                */
/*   Updated: 2026/01/13 by aschweit                 ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe_syntax(t_token *current)
{
	if (current->type == type_Pipe && current->next
		&& current->next->type == type_Pipe)
	{
		ft_putstr_fd("minishell: syntax error near token `|'\n", 2);
		return (0);
	}
	return (1);
}

int	check_redir_syntax(t_token *current)
{
	if (is_redir(current->type) && !current->next)
	{
		ft_putstr_fd("minishell: syntax error near newline\n", 2);
		return (0);
	}
	if (is_redir(current->type) && current->next
		&& current->next->type == type_Pipe)
	{
		ft_putstr_fd("minishell: syntax error near token `|'\n", 2);
		return (0);
	}
	if (is_redir(current->type) && current->next
		&& is_redir(current->next->type))
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		return (0);
	}
	return (1);
}

int	check_syntax(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (current && current->type == type_Pipe)
	{
		ft_putstr_fd("minishell: syntax error near token `|'\n", 2);
		return (0);
	}
	while (current)
	{
		if (!check_pipe_syntax(current))
			return (0);
		if (!check_redir_syntax(current))
			return (0);
		current = current->next;
	}
	return (1);
}