/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                     :+:      :+:    :+:*/
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:31:13 by aschweit       #+#    #+#                */
/*   Updated: 2025/10/08 12:32:07 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tokens(t_token *tokens)
{
    t_token *current;
    char *type_str;

    current = tokens;
    printf("\n-TOKENS-\n");
    while (current)
    {
        if (current->type == type_Word)
            type_str = "W";
        else if (current->type == type_Pipe)
            type_str = "P";
        else if (current->type == type_Redir_in)
            type_str = "RIN";
        else if (current->type == type_Redir_out)
            type_str = "ROUT";
        else if (current->type == type_Redir_app)
            type_str = "RAPP";
        else if (current->type == type_Var)
            type_str = "VAR";
        else if (current->type == type_Var_exit)
            type_str = "VAR_EXIT ($?)";
        else if (current->type == type_Var_pid)
            type_str = "VAR_PID ($$)";
        else
            type_str = "UNK";
        if (current->value)
        {
            printf("[%s: \"%s\"]", type_str, current->value);
            if (current->in_single_quotes)
                printf(" [SINGLE_QUOTES]");
            if (current->in_double_quotes)
                printf(" [DOUBLE_QUOTES]");
            
            printf("\n");
        }
        else
            printf("[%s]\n", type_str);
        
        current = current->next;
    }
    printf("\n");
}

t_token *new_token(t_token_type type, char *value)
{
    t_token *token;

    token = (t_token *)malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = type;
    token->value = value;
    token->next = NULL;
    return (token);
}

void add_token(t_token **head, t_token *new)
{
    t_token *current;

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
char *extract_var_name(char *str, int *i)
{
    int start;
    int len;
    char *var_name;
    int j;

    start = *i;
    if(str[*i] == '?')
    {
        (*i)++;
        var_name = malloc(2);
        if(!var_name)
            return(NULL);
        var_name[0] = '?';
        var_name[1] = '\0';
        return(var_name);
    }

    if(str[*i] == '$')
    {
        (*i)++;
        var_name = malloc(2);
        if(!var_name)
            return(NULL);
        var_name[0] = '$';
        var_name[1] = '\0';
        return(var_name);
    }
    while (str[*i] && is_var_char(str[*i]))
        (*i)++;
    len = *i - start;
    if(len == 0)
        return(NULL);
    var_name = malloc(sizeof(char) * (len + 1));
    if(!var_name)
        return(NULL);
    j = 0;
    while(j < len)
    {
        var_name[j] = str[start + j];
        j++;
    }
    var_name[j] = '\0';
    return(var_name);
}
t_token *extract_word_with_quotes(char *str, int *i)
{
    int start;
    char *word;
    int j;
    t_quote state;
    t_token *token;

    state.in_single = 0;
    state.in_double = 0;
    start = *i;
    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);

    token->type = type_Word;
    token->value = NULL;
    token->in_single_quotes = 0;
    token->in_double_quotes = 0;
    token->next = NULL;

    if (str[*i] == '$' && !state.in_single)
    {
        (*i)++;
        if(str[*i] == '?')
        {
            token->type = type_Var_exit;
            (*i)++;
            word = malloc(2);
            if(!word)
                return(NULL);
            word[0] = '?';
            word[1] = '\0';
            token->value = word;
            return (token);
        }
        if(str[*i] == '$')
        {
            token->type = type_Var_pid;
            (*i)++;
            word = malloc(2);
            if(!word)
                return(NULL);
            word[0] = '$';
            word[1] = '\0';
            token->value = word;
            return (token);
        }
        token->type = type_Var;
        token->value = extract_var_name(str, i);
        if (!token->value)
        {
            free(token);
            return (NULL);
        }
        return (token);
    }
    token->type = type_Word;
    while (str[*i])
    {
        if (str[*i] == '\'' && !state.in_double)
        {
            state.in_single = !state.in_single;
            token->in_single_quotes = 1;
        }
        else if (str[*i] == '"' && !state.in_single)
        {
            state.in_double = !state.in_double;
            token->in_double_quotes = 1;
        }
        
        if (!state.in_single && !state.in_double)
        {
            if (is_space(str[*i]) || is_token_char(str[*i]))
                break;
        }

        (*i)++;
    }

    int len = *i - start;
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

    token->value = word;
    return (token);
}

t_token *tokenize_with_quotes(char *input)
{
    t_token *tokens;
    t_token *new;
    int i;

    tokens = NULL;
    i = 0;
    
    while (input[i])
    {
        while (is_space(input[i]))
            i++;
        
        if (!input[i])
            break;
        
        if (input[i] == '|')
        {
            new = new_token(type_Pipe, NULL);
            add_token(&tokens, new);
            i++;
        }
        else if (input[i] == '>' && input[i + 1] == '>')
        {
            new = new_token(type_Redir_app, NULL);
            add_token(&tokens, new);
            i += 2;
        }    
        else if (input[i] == '>')
        {
            new = new_token(type_Redir_out, NULL);
            add_token(&tokens, new);
            i++;
        }
        else if (input[i] == '<')
        {
            new = new_token(type_Redir_in, NULL);
            add_token(&tokens, new);
            i++;
        }
        else
        {
            new = extract_word_with_quotes(input, &i);
            add_token(&tokens, new);
        }
    }
    return (tokens);
}