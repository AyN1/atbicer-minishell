/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 01:22:52 by aschweit          #+#    #+#             */
/*   Updated: 2026/01/14 01:22:52 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*new_redir(int type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = file;
	redir->next = NULL;
	return (redir);
}

int	process_redir(t_token **current, t_cmd *cmd)
{
	t_redir	*redir;
	char	*file;
	int		type;

	type = (*current)->type;
	*current = (*current)->next;
	if (!*current)
		return (0);
	file = remove_quotes((*current)->value);
	if (!file)
		return (0);
	redir = new_redir(type, file);
	if (!redir)
	{
		free(file);
		return (0);
	}
	add_redir(&cmd->redirs, redir);
	*current = (*current)->next;
	return (1);
}
