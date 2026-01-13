/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:31:13 by aschweit       #+#    #+#                */
/*   Updated: 2026/01/13 by aschweit                 ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_escape_in_dquotes(char *str, int *i, char *res, int *j)
{
	if (str[*i] == '\\' && (str[*i + 1] == '"' || str[*i + 1] == '\\'
			|| str[*i + 1] == '$'))
	{
		(*i)++;
		res[(*j)++] = str[(*i)++];
		return (1);
	}
	return (0);
}

void	process_char_in_quotes(char *str, int *i, char *res, int *j)
{
	char	quote;

	quote = 0;
	while (str[*i])
	{
		if ((str[*i] == '\'' || str[*i] == '"') && !quote)
		{
			quote = str[(*i)++];
			continue ;
		}
		if (str[*i] == quote)
		{
			quote = 0;
			(*i)++;
			continue ;
		}
		if (quote == '"' && handle_escape_in_dquotes(str, i, res, j))
			continue ;
		res[(*j)++] = str[(*i)++];
	}
}

char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	process_char_in_quotes(str, &i, result, &j);
	result[j] = '\0';
	return (result);
}