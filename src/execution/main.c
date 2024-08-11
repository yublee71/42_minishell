/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:37:53 by yublee            #+#    #+#             */
/*   Updated: 2024/08/11 18:33:06 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	wait_if_heredoc(t_ast *cmd_node)
{
	t_ast	*tmp;

	tmp = cmd_node->left;
	while (tmp)
	{
		if (tmp->type == TK_HEREDOC)
			return (1);
		tmp = tmp->left;
	}
	return (0);
}

static void	exec_pipex(t_ast *root, t_info *info, int *status)
{
	int		i;
	pid_t	pid;
	t_ast	*current;
	t_ast	*cmd_node;

	i = -1;
	current = root;
	while (info->cmd_cnt && ++i < info->cmd_cnt)
	{
		if (current->type == TK_PIPE)
			cmd_node = current->left;
		else
			cmd_node = current;
		pid = fork();
		if (pid < 0)
			exit_with_message("fork", EXIT_FAILURE, info);
		if (wait_if_heredoc(cmd_node))
			waitpid(pid, status, 0);
		sleep(1); //only for test
		if (pid == 0)
			child_process(i, cmd_node, info);
		if (i != 0)
			close(info->fds[i - 1][READ_END]);
		if (i != info->cmd_cnt - 1)
			close(info->fds[i][WRITE_END]);
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
	if (info->cmd_cnt == 1)
		child_process(-1, root, info);
	else
		exec_pipex(root, info, &status);
	free_before_exit(info);
	exit(WEXITSTATUS(status));
}
