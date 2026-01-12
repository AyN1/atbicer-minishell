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

// Vérifier si la syntaxe est valide
int check_syntax(t_token *tokens)
{
    t_token *current;

    current = tokens;
    
    // Vérifier qu'on ne commence pas par un pipe
    if (current && current->type == type_Pipe)
    {
        printf("minishell: syntax error near unexpected token `|'\n");
        return (0);
    }
    
    while (current)
    {
        // Deux pipes consécutifs
        if (current->type == type_Pipe && current->next 
            && current->next->type == type_Pipe)
        {
            printf("minishell: syntax error near unexpected token `|'\n");
            return (0);
        }
        
        // Redirection sans fichier
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

// Compter les arguments avant un pipe ou la fin
int count_args(t_token *tokens)
{
    int count;
    t_token *current;

    count = 0;
    current = tokens;
    
    while (current && current->type != type_Pipe)
    {
        if (current->type == type_Word)
            count++;
        current = current->next;
    }
    
    return (count);
}

// Enlever les quotes d'une chaîne
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
            quote = str[i];  // Entrer dans les quotes
            i++;
            continue;
        }
        else if (str[i] == quote)
        {
            quote = 0;  // Sortir des quotes
            i++;
            continue;
        }
        result[j++] = str[i++];
    }
    
    result[j] = '\0';
    return (result);
}

// Construire argv[] depuis les tokens
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
        if (current->type == type_Word)
        {
            argv[i] = remove_quotes(current->value);
            i++;
        }
        current = current->next;
    }
    
    argv[i] = NULL;
    *tokens = current;  // Avancer jusqu'au pipe ou NULL
    
    return (argv);
}

// Créer une nouvelle commande
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

// Parser : tokens → t_cmd
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
        // Créer une nouvelle commande
        t_cmd *cmd = new_cmd();
        
        // Construire argv
        cmd->argv = build_argv(&tok);
        
        // Ajouter à la liste
        if (!head)
            head = cmd;
        else
        {
            current = head;
            while (current->next)
                current = current->next;
            current->next = cmd;
        }
        
        // Sauter le pipe si présent
        if (tok && tok->type == type_Pipe)
            tok = tok->next;
    }
    
    return (head);
}

void print_commands(t_cmd *cmds)
{
    t_cmd *current;
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
        
        current = current->next;
    }
    printf("================\n");
}

void free_commands(t_cmd *cmds)
{
    t_cmd *tmp;
    int i;

    while (cmds)
    {
        tmp = cmds->next;
        
        // Libérer argv
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
        
        // TODO: Libérer redirections
        
        free(cmds);
        cmds = tmp;
    }
}