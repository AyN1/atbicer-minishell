# **************************************************************************** #
#                                    NAME                                      #
# **************************************************************************** #

NAME		= minishell

# **************************************************************************** #
#                                   COMPILER                                   #
# **************************************************************************** #

CC			= cc
# CFLAGS		= -Wall -Wextra -Werror

# **************************************************************************** #
#                                    FILES                                     #
# **************************************************************************** #

SRCS		= minishell.c \
			  command_lexer.c \
			  lexer_utility.c \
			  parser.c \
			  exec.c

OBJS		= $(SRCS:.c=.o)

# **************************************************************************** #
#                                    LIBFT                                     #
# **************************************************************************** #

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a
INCLUDES	= -I. -I$(LIBFT_DIR)

# readline (adjust if needed for your OS/env)
READLINE	= -lreadline -lhistory -lncurses

# **************************************************************************** #
#                                     RULES                                    #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
