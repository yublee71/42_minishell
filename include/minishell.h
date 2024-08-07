/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:55:33 by yublee            #+#    #+#             */
/*   Updated: 2024/08/07 02:41:04 by yublee           ###   ########.fr       */
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
# include "libft.h"
# include "get_next_line.h"
# define READ_END 0
# define WRITE_END 1

typedef struct s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
}	t_btree;

typedef struct s_info
{
	int		cmd_cnt;
	char	**env;
	int		**fds;
	t_btree	*root;
	t_list	**cmd_list;
}	t_info;

typedef enum e_token_type
{
	TK_WORD = 1 << 0,
	TK_PIPE = 1 << 1,
	TK_INPUT = 1 << 2,
	TK_OUTPUT = 1 << 3,
	TK_APPEND = 1 << 4,
	TK_HEREDOC = 1 << 5,
	TK_SQUOTE = 1 << 6,
	TK_DQUOTE = 1 << 7
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}	t_token;

//parser
t_list	*parser(char *cmd, char **env);

//pipex
void	pipex(t_list **cmd_list, t_btree *root, char **env);
void	get_input(t_btree *cmd, int i, t_info info);
void	get_output(t_btree *cmd, int i, t_info info);
void	child_process(int i, t_list *current, t_info info);
char	**get_argv(char *str, char **env);

//tree utils
void	print_node(void *item);
void	free_node(t_btree *root);
t_btree	*create_node(void *item);
void	btree_apply_infix(t_btree *root, void (*applyf)(void *));
void	btree_apply_suffix(t_btree *root, void (*applyf)(t_btree *));

//str utils
char	**ft_split_except_quoted_part(char *s, char *s_sub, char c);
void	ft_strtrim_and_free(t_btree *root);

//token utils
void	free_token(void *content);
void	print_token(void *content);

//utils
void	free_before_exit(t_info	info);
void	exit_with_message(char *str, int exit_no, t_info info);
void	free_str_array(char **array);
int		free_fds(int **fds, int i);
void	add_random_str_to_str(char *buf, size_t buf_size, char *str, size_t rand_cnt);

#endif