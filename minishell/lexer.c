/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:31:13 by aschweit          #+#    #+#             */
/*   Updated: 2026/01/14 01:14:18 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->in_single_quotes = 0;
	token->in_double_quotes = 0;
	token->next = NULL;
	return (token);
}

void	update_quote_state(char c, t_quote *state, t_token *token)
{
	if (c == '\'' && !state->in_double)
	{
		state->in_single = !state->in_single;
		token->in_single_quotes = 1;
	}
	else if (c == '"' && !state->in_single)
	{
		state->in_double = !state->in_double;
		token->in_double_quotes = 1;
	}
}

t_token	*extract_word_with_quotes(char *str, int *i)
{
	int		start;
	t_quote	state;
	t_token	*token;

	if (str[*i] == '$')
		return (handle_var(str, i));
	state.in_single = 0;
	state.in_double = 0;
	start = *i;
	token = init_token();
	if (!token)
		return (NULL);
	token->type = type_Word;
	while (str[*i])
	{
		update_quote_state(str[*i], &state, token);
		if (!state.in_single && !state.in_double)
			if (is_space(str[*i]) || is_token_char(str[*i]))
				break ;
		(*i)++;
	}
	token->value = copy_word(str, start, *i);
	return (token);
}

t_token	*tokenize_with_quotes(char *input)
{
	t_token	*tokens;
	t_token	*new;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		if (input[i] == '|')
			add_pipe(&tokens, &i);
		else if (input[i] == '>')
			add_redir_out(&tokens, input, &i);
		else if (input[i] == '<')
			add_redir_in(&tokens, input, &i);
		else
		{
			new = extract_word_with_quotes(input, &i);
			add_token(&tokens, new);
		}
	}
	return (tokens);
}
