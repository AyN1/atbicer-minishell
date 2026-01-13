/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utility.c                         :+:      :+:    :+:*/
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:31:13 by aschweit       #+#    #+#                */
/*   Updated: 2025/10/08 12:32:07 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_space(char c)
{
    return(c == ' ' || c == '\t' || c == '\n'|| 
            c == '\v' || c == '\f' || c == '\r');
}

int is_token_char(char c)
{
    return(c == '|' || c == '<' || c == '>');
}

int is_var_char(char c)
{
    return ((c >= 'a' && c <= 'z') || 
            (c >= 'A' && c <= 'Z') || 
            (c >= '0' && c <= '9') || 
            c == '_');
}

t_token	*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type_Word;
	token->value = NULL;
	token->in_single_quotes = 0;
	token->in_double_quotes = 0;
	token->next = NULL;
	return (token);
}

void free_tokens(t_token *tokens)
{
    t_token *tmp;

    while (tokens)
    {
        tmp = tokens->next;
        if (tokens->value)
            free(tokens->value);
        free(tokens);
        tokens = tmp;
    }
}