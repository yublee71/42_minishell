/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:58:50 by yublee            #+#    #+#             */
/*   Updated: 2024/08/15 14:08:41 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void		dup_redir_output_to_stdout(t_ast *out_node, t_info *info)
{
	int		fd_output;
	t_ast	*file_node;

	file_node = out_node->right;
	fd_output = -1;
	if (out_node->type == TK_OUTPUT)
		fd_output = open(file_node->value, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (out_node->type == TK_APPEND)
		fd_output = open(file_node->value, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (fd_output < 0 || dup2(fd_output, STDOUT_FILENO) < 0)
		exit_with_message(file_node->value, EXIT_FAILURE, info);
	close(fd_output);
}


void	set_stdout(int i, t_ast *cmd, t_info *info)
{
	t_ast	*out_node;

	if (i != info->cmd_cnt - 1 && i != -1)
	{
		close(info->fds[i][READ_END]);
		if (dup2(info->fds[i][WRITE_END], STDOUT_FILENO) < 0)
			exit_with_message("dup2", EXIT_FAILURE, info);
		close(info->fds[i][WRITE_END]);
	}
	out_node = cmd->right;
	while (out_node)
	{
		dup_redir_output_to_stdout(out_node, info);
		out_node = out_node->right->right;
	}
}