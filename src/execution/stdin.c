/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:59:05 by yublee            #+#    #+#             */
/*   Updated: 2024/12/09 18:12:56 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	dup_redir_input_to_stdin_builtin(t_ast *in_node, t_info *info)
{
	int			fd_input;
	t_ast		*file_node;
	const char	*err_msg = ": No such file or directory\n";

	file_node = in_node->left;
	fd_input = -1;
	if (in_node->type == TK_HEREDOC)
		handle_heredoc_input(file_node->value, info);
	else if (in_node->type == TK_INPUT)
	{
		fd_input = open(file_node->value, O_RDONLY);
		if (fd_input < 0)
		{
			write(2, file_node->value, ft_strlen(file_node->value));
			write(2, err_msg, ft_strlen(err_msg));
			*(info->status) = 127;
		}
		else if (dup2(fd_input, STDIN_FILENO) < 0)
			exit_with_message(file_node->value, EXIT_FAILURE, info);
		else
			close(fd_input);
	}
}

static void	dup_redir_input_to_stdin(t_ast *in_node, t_info *info)
{
	int		fd_input;
	t_ast	*file_node;

	file_node = in_node->left;
	fd_input = -1;
	if (in_node->type == TK_HEREDOC)
		handle_heredoc_input(file_node->value, info);
	else if (in_node->type == TK_INPUT)
	{
		fd_input = open(file_node->value, O_RDONLY);
		if (fd_input < 0 || dup2(fd_input, STDIN_FILENO) < 0)
			exit_with_message(file_node->value, EXIT_FAILURE, info);
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
