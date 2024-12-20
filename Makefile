# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yublee <yublee@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/19 14:55:22 by yublee            #+#    #+#              #
#    Updated: 2024/12/09 21:14:55 by yublee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= minishell
CC				:= cc
# INC_DIR			=  ./include
# INCLUDE_FLAGS	:= -I. -I$(INC_DIR) -I/usr/include
OPTIMIZE_FLAGS	:= -O0
DEBUG_FLAGS		:= -g3 -gdwarf-3
MANDATORY_FLAGS	:= -Wall -Wextra -Werror -Wimplicit
CFLAGS			= $(MANDATORY_FLAGS) $(DEBUG_FLAGS) $(OPTIMIZE_FLAGS)

LIBFT_DIR		=  ./lib/ft
LIBFT_LIB		=  $(LIBFT_DIR)/libft.a
LIBS			:= $(LIBFT)
LINK_FLAGS		:= -L $(LIBFT_DIR) -lft -lreadline

SRCS			= \
					src/main.c \
					src/parsing/build_tree.c \
					src/parsing/expansion.c \
					src/parsing/heredoc.c \
					src/parsing/main.c \
					src/parsing/post_syntax_validation.c \
					src/parsing/pre_syntax_validation.c \
					src/parsing/tokenization.c \
					src/parsing/utils_args.c \
					src/parsing/utils_expansion.c \
					src/parsing/utils_quote.c \
					src/parsing/utils.c \
					src/init_execution/main.c \
					src/execution/child_process.c \
					src/execution/exec_builtin.c \
					src/execution/main.c \
					src/execution/stdin.c \
					src/execution/stdout.c \
					src/utils/exit.c \
					src/utils/utils_array.c \
					src/utils/utils_token.c \
					src/utils/utils_tree.c \
					src/utils/signal.c \
					src/utils/env.c \
					src/builtin/ft_cd.c \
					src/builtin/ft_echo.c \
					src/builtin/ft_export.c \
					src/builtin/ft_pwd.c \
					src/builtin/ft_unset.c \
					src/builtin/ft_env.c \
					src/builtin/ft_exit.c \
					src/builtin/main.c \

BUILD_DIR		= build
OBJS			= $(SRCS:%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJS)
		$(CC) $(OBJS) -g -o $@ $(LINK_FLAGS)

$(LIBFT_LIB):
		@$(MAKE) -C $(LIBFT_DIR) -j8

$(BUILD_DIR)/%.o: %.c
		@if [ ! -d $(@D) ]; then mkdir -pv $(@D); fi
		$(CC) $(CFLAGS) -c $^ -o $@

clean:
		$(RM) -rf $(BUILD_DIR)
		$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
		$(RM) $(RMFLAGS) $(NAME)
		$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

norm:
		@norminette $(SRCS)
		@$(MAKE) -C $(LIBFT_DIR) norm

.PHONY: all clean fclean re bonus norm
