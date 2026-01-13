/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschweit <aschweit@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:31:13 by aschweit       #+#    #+#                */
/*   Updated: 2026/01/12 18:01:03 by aschweit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

struct termios g_original_term;

void setup_terminal(void)
{
    struct termios term;
    tcgetattr(STDIN_FILENO, &g_original_term);
	term = g_original_term;
    term.c_lflag &= ~ECHOCTL;  
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void restore_terminal(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &g_original_term);
}

/*int environment_variables(char const * envp)
{
    char *value;

    value = getenv(envp);
    if(value)
        printf("%s = %s\n", envp , value);
    else
        return (0);
    return(1);
}
void launch_executable(const char * path, char const ** args, char const ** envp)
{
    execve(path, args, envp);
}*/
void handle_sigint(int sig)
{
    (void)sig;
    write(1, "\n", 1); 
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int main(int argc, char **argv, char **envp) // added argument instead of void.
{
    t_token *tokens;
    char *line_input;
    int end = 0;
    t_cmd *cmds; 
   
    (void)argc;
    (void)argv;
	setup_terminal(); 
    signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN); 
    while(!end)
    {
        line_input = readline("minishell> ");
        if(!line_input /*|| exit_line(line_input)*/)
        {
            printf("exit\n");
            break;
        }
        if(!*line_input)
        { 
            free(line_input);
            continue;
        }
        if((strcmp(line_input , "exit") == 0))
        {
            free(line_input);
            break;
        }
        add_history(line_input);
        tokens = tokenize_with_quotes(line_input);
        // print_tokens(tokens);
        cmds = parse(tokens);
        execute_cmds(cmds, envp); // atbicer
        // print_commands(cmds);
        /*execute_command(line_input);*/
        // print_tokens(tokens);
        free_tokens(tokens);
        free_commands(cmds);
        free(line_input);
    }
	restore_terminal();
    rl_clear_history();
	return (0);
}
