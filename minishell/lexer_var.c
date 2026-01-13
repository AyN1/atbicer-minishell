/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:31:13 by aschweit       #+#    #+#                */
/*   Updated: 2026/01/13 by aschweit                 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_normal_var(char *str, int start, int end)
{
	char	*var_name;
	int		len;
	int		j;

	len = end - start;
	if (len == 0)
		return (NULL);
	var_name = malloc(sizeof(char) * (len + 1));
	if (!var_name)
		return (NULL);
	j = 0;
	while (j < len)
	{
		var_name[j] = str[start + j];
		j++;
	}
	var_name[j] = '\0';
	return (var_name);
}

char	*create_special_var(char c)
{
	char	*var_name;

	var_name = malloc(2);
	if (!var_name)
		return (NULL);
	var_name[0] = c;
	var_name[1] = '\0';
	return (var_name);
}

char	*extract_var_name(char *str, int *i)
{
	int	start;

	start = *i;
	if (str[*i] == '?')
	{
		(*i)++;
		return (create_special_var('?'));
	}
	if (str[*i] == '$')
	{
		(*i)++;
		return (create_special_var('$'));
	}
	while (str[*i] && is_var_char(str[*i]))
		(*i)++;
	return (extract_normal_var(str, start, *i));
}

t_token	*create_var_token(t_token_type type, char c)
{
	t_token	*token;
	char	*word;

	token = init_token();
	if (!token)
		return (NULL);
	token->type = type;
	word = malloc(2);
	if (!word)
	{
		free(token);
		return (NULL);
	}
	word[0] = c;
	word[1] = '\0';
	token->value = word;
	return (token);
}

t_token	*handle_var(char *str, int *i)
{
	t_token	*token;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (create_var_token(type_Var_exit, '?'));
	}
	if (str[*i] == '$')
	{
		(*i)++;
		return (create_var_token(type_Var_pid, '$'));
	}
	token = init_token();
	if (!token)
		return (NULL);
	token->type = type_Var;
	token->value = extract_var_name(str, i);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	return (token);
}