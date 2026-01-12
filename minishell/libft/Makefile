# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/29 04:40:04 by atbicer           #+#    #+#              #
#    Updated: 2025/05/13 05:27:44 by atbicer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -Iinclude
RM = rm -rf

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
SRC_CHAR = ft_isdigit.c ft_isascii.c ft_isprint.c ft_isalpha.c ft_isalnum.c ft_toupper.c ft_tolower.c ft_isspace.c
SRC_STRING = ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strnstr.c \
             ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_strmapi.c ft_striteri.c
SRC_MEMORY = ft_bzero.c ft_memcpy.c ft_memset.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_calloc.c
SRC_CONVERSION = ft_atoi.c ft_atol.c ft_itoa.c
SRC_OUTPUT = ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
SRC_LIST = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
           ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
SRC_PRINTF = ft_printf.c ft_print_digit.c ft_print_ptr.c ft_print_str.c
SRC_GNL = get_next_line.c

# Combine all source files
SRCS = $(addprefix $(SRC_DIR)/char/, $(SRC_CHAR)) \
       $(addprefix $(SRC_DIR)/string/, $(SRC_STRING)) \
       $(addprefix $(SRC_DIR)/memory/, $(SRC_MEMORY)) \
       $(addprefix $(SRC_DIR)/conversion/, $(SRC_CONVERSION)) \
       $(addprefix $(SRC_DIR)/output/, $(SRC_OUTPUT)) \
       $(addprefix $(SRC_DIR)/list/, $(SRC_LIST)) \
       $(addprefix $(SRC_DIR)/printf/, $(SRC_PRINTF)) \
	   $(addprefix $(SRC_DIR)/gnl/, $(SRC_GNL))

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Progress bar variables
TOTAL_FILES := $(words $(SRCS))
CURRENT_FILE := 0
BAR_LENGTH := 30

# Progress bar function - use with $(call progress_bar,filename)
define progress_bar
    $(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
    $(eval PERCENTAGE=$(shell echo $$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES)))))
    $(eval IS_LAST=$(shell if [ $(CURRENT_FILE) -eq $(TOTAL_FILES) ]; then echo 1; else echo 0; fi))
    $(eval HASH_COUNT=$(shell if [ $(IS_LAST) -eq 1 ]; then echo $(BAR_LENGTH); else echo $$(($(CURRENT_FILE) * $(BAR_LENGTH) / $(TOTAL_FILES))); fi))
    $(eval SPACE_COUNT=$(shell echo $$(($(BAR_LENGTH) - $(HASH_COUNT)))))
    @printf "\r[%-$(BAR_LENGTH)s] %3d%% (%d/%d) %-20s" "$$(printf '%0.s#' $$(seq 1 $(HASH_COUNT)))" $(PERCENTAGE) $(CURRENT_FILE) $(TOTAL_FILES) "$(1)"
endef

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@echo "\n$(GREEN)Building libft...$(RESET)"
	@ar rcs $(NAME) $(OBJS)
	@echo "$(GREEN)libft compiled$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(call progress_bar,$(notdir $<))
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@echo "$(RED)[LIBFT] Cleaning object files...$(RESET)"
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "$(RED)[LIBFT] Cleaning everything...$(RESET)"
	@$(RM) $(NAME)


re: fclean all

.PHONY: all clean fclean re
