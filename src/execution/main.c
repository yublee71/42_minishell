/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:37:53 by yublee            #+#    #+#             */
/*   Updated: 2024/12/09 01:30:41 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	wait_if_heredoc(t_ast *cmd_node, pid_t pid, int *status)
{
	t_ast	*tmp;

	tmp = cmd_node->left;
	while (tmp)
	{
		if (tmp->type == TK_HEREDOC)
		{
			waitpid(pid, status, 0);
			return ;
		}
		tmp = tmp->left;
	}
	return ;
}

static void	close_pipe_for_parent(int i, t_info *info)
{
	if (i != 0)
		close(info->fds[i - 1][READ_END]);
	if (i != info->cmd_cnt - 1)
		close(info->fds[i][WRITE_END]);
}

static void	exec_pipex(t_ast *root, t_info *info, int *status)
{
	int		i;
	pid_t	pid;
	t_ast	*current;
	t_ast	*cmd_node;

	i = -1;
	current = root;
	while (++i < info->cmd_cnt)
	{
		if (current->type == TK_PIPE)
			cmd_node = current->left;
		else
			cmd_node = current;
		pid = fork();
		if (pid < 0)
			exit_with_message("fork", EXIT_FAILURE, info);
		wait_if_heredoc(cmd_node, pid, status);
		if (pid == 0)
			child_process(i, cmd_node, info);
		close_pipe_for_parent(i, info);
		current = current->right;
	}
	waitpid(pid, status, 0);
	while (wait(NULL) != -1)
		;
}

void	executor(t_ast *root, t_info *info)
{
	int		status;

	status = 0;
	if (info->cmd_cnt == 1 && which_builtin(root->value) >= 0)
		exec_builtin(root, info);
	else
	{
		exec_pipex(root, info, &status);
		*(info->status) = WEXITSTATUS(status);
	}
	free_before_exit(info, 1);
}
