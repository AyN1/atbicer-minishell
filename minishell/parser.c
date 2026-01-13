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

int is_redir(t_token_type type)
{
    return (type == type_Redir_in || type == type_Redir_out ||
            type == type_Redir_append || type == type_Redir_app);
}

t_redir *new_redir(int type, char *file)
{
    t_redir *redir;

    redir = malloc(sizeof(t_redir));
    if (!redir)
        return (NULL);
    redir->type = type;
    redir->file = file;
    redir->next = NULL;
    return (redir);
}

void add_redir(t_redir **head, t_redir *new)
{
    t_redir *current;

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

t_redir *parse_redir(t_token **tokens)
{
    t_redir *redir;
    t_token *current;
    int type;
    char *file;

    current = *tokens;
    if (!current || !is_redir(current->type))
        return (NULL);
    
    type = current->type;
    
    current = current->next;
    if (!current || current->type != type_Word)
        return (NULL);
    
    file = remove_quotes(current->value);
    
    redir = new_redir(type, file);
    
    *tokens = current->next;
    
    return (redir);
}
int check_syntax(t_token *tokens)
{
    t_token *current;

    current = tokens;
    
    if (current && current->type == type_Pipe)
    {
        printf("minishell: syntax error near unexpected token `|'\n");
        return (0);
    }
    
    while (current)
    {
        if (current->type == type_Pipe && current->next 
            && current->next->type == type_Pipe)
        {
            printf("minishell: syntax error near unexpected token `|'\n");
            return (0);
        }

        if (is_redir(current->type) && !current->next)
        {
            printf("minishell: syntax error near unexpected token `newline'\n");
            return (0);
        }
        
        if (is_redir(current->type) && current->next 
            && current->next->type == type_Pipe)
        {
            printf("minishell: syntax error near unexpected token `|'\n");
            return (0);
        }
        
        if (is_redir(current->type) && current->next 
            && is_redir(current->next->type))
        {
            printf("minishell: syntax error near unexpected token\n");
            return (0);
        }
        
        if ((current->type == type_Redir_in || current->type == type_Redir_out 
            || current->type == type_Redir_app) && !current->next)
        {
            printf("minishell: syntax error near unexpected token `newline'\n");
            return (0);
        }
        
        current = current->next;
    }
    
    return (1);
}

int count_args(t_token *tokens)
{
    int count;
    t_token *current;

    count = 0;
    current = tokens;
    
    while (current && current->type != type_Pipe)
    {
        if (is_redir(current->type))
        {
            current = current->next;
            if (current)
                current = current->next;
            continue;
        }
        if (current->type == type_Word || current->type == type_Var ||
            current->type == type_Var_exit || current->type == type_Var_pid)
            count++;
        current = current->next;
    }
    return (count);
}

char *remove_quotes(char *str)
{
    char *result;
    int i;
    int j;
    char quote;

    if (!str)
        return (NULL);
    
    result = malloc(strlen(str) + 1);
    if (!result)
        return (NULL);
    
    i = 0;
    j = 0;
    quote = 0;
    
    while (str[i])
    {
        if ((str[i] == '\'' || str[i] == '"') && !quote)
        {
            quote = str[i];
            i++;
            continue;
        }
        else if (str[i] == quote)
        {
            quote = 0;
            i++;
            continue;
        }
        result[j++] = str[i++];
    }
    
    result[j] = '\0';
    return (result);
}

char **build_argv(t_token **tokens)
{
    char **argv;
    int count;
    int i;
    t_token *current;

    count = count_args(*tokens);
    argv = malloc(sizeof(char *) * (count + 1));
    if (!argv)
        return (NULL);
    
    i = 0;
    current = *tokens;
    
    while (current && current->type != type_Pipe)
    {
        if (is_redir(current->type))
        {
            current = current->next;
            if (current)
                current = current->next;
            continue;
        }
        if (current->type == type_Word)
        {
            argv[i] = remove_quotes(current->value);
            i++;
        }
        else if (current->type == type_Var || current->type == type_Var_exit 
                 || current->type == type_Var_pid)
        {
            argv[i] = strdup(current->value);
            i++;
        }
        current = current->next;
    }
    
    argv[i] = NULL;
    *tokens = current;  // Avancer jusqu'au pipe ou NULL
    
    return (argv);
}

t_cmd *new_cmd(void)
{
    t_cmd *cmd;

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->argv = NULL;
    cmd->redirs = NULL;
    cmd->next = NULL;
    return (cmd);
}

t_cmd *parse(t_token *tokens)
{
    t_cmd *head;
    t_cmd *current;
    t_token *tok;

    if (!check_syntax(tokens))
        return (NULL);
    
    head = NULL;
    tok = tokens;
    
    while (tok)
    {
        t_cmd *cmd = new_cmd();
        
        cmd->argv = build_argv(&tok);
        
        if (!head)
            head = cmd;
        else
        {
            current = head;
            while (current->next)
                current = current->next;
            current->next = cmd;
        }
        
        if (tok && tok->type == type_Pipe)
            tok = tok->next;
    }
    
    return (head);
}

void print_commands(t_cmd *cmds)
{
    t_cmd *current;
    t_redir *redir;
    int i;
    int cmd_num;

    current = cmds;
    cmd_num = 1;
    
    printf("\n=== COMMANDS ===\n");
    while (current)
    {
        printf("Command %d:\n", cmd_num++);
        printf("  argv: [");
        
        i = 0;
        while (current->argv && current->argv[i])
        {
            printf("\"%s\"", current->argv[i]);
            if (current->argv[i + 1])
                printf(", ");
            i++;
        }
        printf("]\n");

        if (current->redirs)
        {
            printf("  redirections:\n");
            redir = current->redirs;
            while (redir)
            {
                printf("    ");
                if (redir->type == type_Redir_in)
                    printf("< ");
                else if (redir->type == type_Redir_out)
                    printf("> ");
                else if (redir->type == type_Redir_append)
                    printf(">> ");
                else if (redir->type == type_Redir_app)
                    printf("<< ");
                printf("\"%s\"\n", redir->file);
                redir = redir->next;
            }
        }
        current = current->next;
    }
    printf("================\n");
}

void free_commands(t_cmd *cmds)
{
    t_cmd *tmp;
    t_redir *redir;
    t_redir *tmp_redir;
    int i;

    while (cmds)
    {
        tmp = cmds->next;
        
        if (cmds->argv)
        {
            i = 0;
            while (cmds->argv[i])
            {
                free(cmds->argv[i]);
                i++;
            }
            free(cmds->argv);
        }
        
        redir = cmds->redirs;
        while (redir)
        {
            tmp_redir = redir->next;
            if (redir->file)
                free(redir->file);
            free(redir);
            redir = tmp_redir;
        }
        
        free(cmds);
        cmds = tmp;
    }
}