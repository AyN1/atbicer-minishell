/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:31:13 by aschweit       #+#    #+#                */
/*   Updated: 2026/01/13 by aschweit                 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_word(char *str, int *i, t_quote *state)
{
	while (str[*i])
	{
		update_quote_state(str[*i], state, NULL);
		if (!state->in_single && !state->in_double)
			if (is_space(str[*i]) || is_token_char(str[*i]))
				break ;
		(*i)++;
	}
}

char	*copy_word(char *str, int start, int end)
{
	char	*word;
	int		len;
	int		j;

	len = end - start;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	j = 0;
	while (j < len)
	{
		word[j] = str[start + j];
		j++;
	}
	word[j] = '\0';
	return (word);
}