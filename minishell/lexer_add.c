/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 23:02:40 by atbicer           #+#    #+#             */
/*   Updated: 2026/01/13 06:47:40 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_token **head, t_token *new)
{
	t_token	*current;

	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	add_pipe(t_token **tokens, int *i)
{
	t_token	*new;

	new = new_token(type_Pipe, NULL);
	add_token(tokens, new);
	(*i)++;
}

void	add_redir_out(t_token **tokens, char *input, int *i)
{
	t_token	*new;

	if (input[*i + 1] == '>')
	{
		new = new_token(type_Redir_append, NULL);
		add_token(tokens, new);
		(*i) += 2;
	}
	else
	{
		new = new_token(type_Redir_out, NULL);
		add_token(tokens, new);
		(*i)++;
	}
}

void	add_redir_in(t_token **tokens, char *input, int *i)
{
	t_token	*new;

	if (input[*i + 1] == '<')
	{
		new = new_token(type_Redir_app, NULL);
		add_token(tokens, new);
		(*i) += 2;
	}
	else
	{
		new = new_token(type_Redir_in, NULL);
		add_token(tokens, new);
		(*i)++;
	}
}
