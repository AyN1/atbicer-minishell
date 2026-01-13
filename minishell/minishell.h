/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:31:13 by aschweit          #+#    #+#             */
/*   Updated: 2026/01/13 22:15:51 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include "libft.h"

typedef enum token_type
{
    type_Word,
    type_Pipe,       // "|"
    type_Redir_in,     // "<"
    type_Redir_app,      // "<<"
    type_Redir_out,    // ">"
    type_Redir_append,     // ">>"
    type_Var,   // "$"
    type_Var_exit,
    type_Var_pid

}   t_token_type;

typedef struct s_token
{
    t_token_type    type;
    char            *value;
    int             in_single_quotes;
    int             in_double_quotes;
    struct s_token  *next;
}   t_token;

typedef struct s_quote
{
    int in_single; 
    int in_double;  
}   t_quote;

typedef struct s_redir
{
    int             type;
    char            *file;
    struct s_redir  *next;
}   t_redir;

typedef struct s_cmd
{
    char            **argv;
    t_redir         *redirs;
    struct s_cmd    *next;
}   t_cmd;

extern struct termios g_original_term;

t_token *tokenize_with_quotes(char *input);
t_token *extract_word_with_quotes(char *str, int *i);
t_token *new_token(t_token_type type, char *value);
char    *extract_var_name(char *str, int *i);
int is_token_char(char c);
int is_space(char c);
int is_var_char(char c);
void    add_token(t_token **head, t_token *new);
void print_tokens(t_token *tokens);
void free_tokens(t_token *tokens);
void free_commands(t_cmd *cmds);
t_cmd *parse(t_token *tokens);
char **build_argv(t_token **tokens);
t_cmd *new_cmd(void);
void print_commands(t_cmd *cmds);
int is_redir(t_token_type type);
t_redir *new_redir(int type, char *file);
void add_redir(t_redir **head, t_redir *new);
t_redir *parse_redir(t_token **tokens);
int check_syntax(t_token *tokens);
char *remove_quotes(char *str);
int execute_cmds(t_cmd *cmds, char **envp);

/* builtin functions */
int builtin_pwd(void);


#endif
