/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:55:33 by yublee            #+#    #+#             */
/*   Updated: 2024/12/02 21:07:24 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft.h"
# include "get_next_line.h"
# define READ_END 0
# define WRITE_END 1

extern int	g_sigint_received;

typedef enum e_token_type
{
	TK_PIPE = 1 << 0,
	TK_INPUT = 1 << 1,
	TK_HEREDOC = 1 << 2,
	TK_OUTPUT = 1 << 3,
	TK_APPEND = 1 << 4,
	TK_WORD = 1 << 5,
	TK_FILE = 1 << 6,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}	t_token;

//AST: Abstract Syntax Tree
typedef struct s_ast
{
	struct s_ast	*left;
	struct s_ast	*right;
	t_token_type	type;
	char			*value;
	char			**args;
}	t_ast;

typedef struct s_info
{
	int		cmd_cnt;
	char	**env;
	int		**fds;
	t_ast	*root;
}	t_info;

//parser
t_ast	*parser(char *cmd, char **env);

//execution initiation
t_info	init_executor(t_ast *root, char **env);

//execution
void	executor(t_ast *root, t_info *info);

//tree utils
void	ast_print_node(t_ast *node);
void	ast_free_node(t_ast *node);
t_ast	*ast_new_node(t_token *token);
void	ast_apply_infix(t_ast *node, void (*applyf)(t_ast *));
void	ast_apply_suffix(t_ast *node, void (*applyf)(t_ast *));

//token utils
void	free_token(void *content);
void	print_token(void *content);

//array utils
void	free_array(void **array);
void	free_array_until(void **array, int i);

//exit
void	exit_with_message(char *str, int exit_no, t_info *info);
void	free_before_exit(t_info	*info);

//signal
void	handle_sigint(int sig);
void	handle_sigint_heredoc(int sig);

#endif