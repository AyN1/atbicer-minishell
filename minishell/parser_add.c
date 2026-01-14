/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2026/01/14 01:22:35 by aschweit          #+#    #+#             */
/*   Updated: 2026/01/14 01:22:35 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redir(t_redir **head, t_redir *new)
{
	t_redir	*current;

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

void	add_word(t_token *curr, char **argv, int *i)
{
	if (curr->type == type_Word)
		argv[(*i)++] = remove_quotes(curr->value);
	else if (curr->type == type_Var || curr->type == type_Var_exit
		|| curr->type == type_Var_pid)
		argv[(*i)++] = ft_strdup(curr->value);
}

void	add_cmd(t_cmd **head, t_cmd *new)
{
	t_cmd	*current;

	if (!*head)
		*head = new;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}
