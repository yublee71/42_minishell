/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:59:05 by yublee            #+#    #+#             */
/*   Updated: 2024/12/11 16:58:17 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	dup_redir_input_to_stdin_builtin(t_ast *in_node, t_info *info)
{
	int			fd_input;
	t_ast		*file_node;
	char		*err_msg;

	file_node = in_node->left;
	if (in_node->type != TK_HEREDOC && in_node->type != TK_INPUT)
		return ;
	err_msg = ": No such file or directory\n";
	fd_input = -1;
	if (in_node->type == TK_INPUT)
		fd_input = open(file_node->value, O_RDONLY);
	else if (in_node->type == TK_HEREDOC)
	{
		fd_input = in_node->heredoc_fd;
		err_msg = "heredoc";
	}
	if (fd_input < 0)
	{
		perror(file_node->value);
		*(info->status) = 127;
		return ;
	}
	else if (dup2(fd_input, STDIN_FILENO) < 0)
		exit_with_message(file_node->value, EXIT_FAILURE, info);
	close(fd_input);
}

static void	dup_redir_input_to_stdin(t_ast *in_node, t_info *info)
{
	int			fd_input;
	t_ast		*file_node;

	file_node = in_node->left;
	fd_input = -1;
	if (in_node->type == TK_HEREDOC)
	{
		if (dup2(in_node->heredoc_fd, STDIN_FILENO) < 0)
			exit_with_message("heredoc", EXIT_FAILURE, info);
		close(in_node->heredoc_fd);
	}
	else if (in_node->type == TK_INPUT)
	{
		fd_input = open(file_node->value, O_RDONLY);
		if (fd_input < 0 || dup2(fd_input, STDIN_FILENO) < 0)
		{
			write(2, file_node->value, ft_strlen(file_node->value));
			write(2, ": ", 2);
			exit_with_message(NULL, EXIT_FAILURE, info);
		}
		close(fd_input);
	}
}

void	set_stdin(int i, t_ast *cmd, t_info *info)
{
	t_ast	*in_node;

	if (i != 0 && i != -1)
	{
		close(info->fds[i - 1][WRITE_END]);
		if (dup2(info->fds[i - 1][READ_END], STDIN_FILENO) < 0)
			exit_with_message("dup2", EXIT_FAILURE, info);
		close(info->fds[i - 1][READ_END]);
	}
	in_node = cmd->left;
	while (in_node)
	{
		if (i != -1)
			dup_redir_input_to_stdin(in_node, info);
		else
			dup_redir_input_to_stdin_builtin(in_node, info);
		in_node = in_node->left->left;
	}
}
