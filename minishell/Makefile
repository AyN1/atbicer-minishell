NAME        := minishell

CC          := cc
CFLAGS      := -Wall -Wextra -Werror
RM          := rm -f

OBJ_DIR     := obj
LIBFT_DIR   := libft
LIBFT       := $(LIBFT_DIR)/libft.a

SRCS        := minishell.c \
               command_lexer.c \
               lexer_utility.c \
               parser.c \
			   exec.c \
			   builtins_pwd.c

OBJS        := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

INCLUDES    := -I. -I$(LIBFT_DIR)/include

# ===================================================== #
# OS detection
# ===================================================== #
UNAME := $(shell uname)

ifeq ($(UNAME),Darwin)
	READLINE_INC := -I$(shell brew --prefix readline)/include
	READLINE_LIB := -L$(shell brew --prefix readline)/lib
	READLINE_LNK := -lreadline -lhistory -lncurses
else
	READLINE_INC :=
	READLINE_LIB :=
	READLINE_LNK := -lreadline
endif

CFLAGS  += $(READLINE_INC)
LDFLAGS := $(READLINE_LIB)
LDLIBS  := $(LIBFT) $(READLINE_LNK)

# ===================================================== #

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c minishell.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
