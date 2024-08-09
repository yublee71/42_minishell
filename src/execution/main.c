/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:37:53 by yublee            #+#    #+#             */
/*   Updated: 2024/08/09 04:18:32 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	**create_pipeline(int cnt)
{
	int	**fds;
	int	i;

	fds = (int **)malloc(cnt * sizeof(int *));
	if (!fds)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < cnt)
	{
		fds[i] = malloc(2 * sizeof(int));
		if (!fds[i])
		{
			free_fds(fds, i);
			exit(EXIT_FAILURE);
		}
		if (pipe(fds[i]) < 0)
		{
			free_fds(fds, i + 1);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (fds);
}

static int	wait_if_heredoc(void *content)
{
	t_ast	*tmp;
	char	*str;

	tmp = (t_ast *)content;
	tmp = tmp->left;
	while (tmp)
	{
		str = (char *)tmp->item;
		if (str && str[0] == '<' && str[1] == '<')
			return (-1);
		tmp = tmp->left;
	}
	return (0);
}

static void	exec_pipex(t_info info, t_list **cmd_list, int *status)
{
	int		i;
	pid_t	pid;
	t_list	*current;

	i = -1;
	current = *cmd_list;
	while (info.cmd_cnt && ++i < info.cmd_cnt)
	{
		pid = fork();
		if (pid < 0)
			exit_with_message("fork", EXIT_FAILURE, info);
		if (wait_if_heredoc(current->content))
			waitpid(pid, status, 0);
		sleep(1); //only for test
		if (pid == 0)
			child_process(i, current, info);
		if (i != 0)
			close(info.fds[i - 1][READ_END]);
		if (i != info.cmd_cnt - 1)
			close(info.fds[i][WRITE_END]);
		current = current->next;
	}
	waitpid(pid, status, 0);
	free_before_exit(info);
	while (wait(NULL) != -1)
		;
}

void	pipex(t_list **cmd_list, t_ast *root, char **env)
{
	int		status;

	status = 0;
	info.fds = create_pipeline(info.cmd_cnt - 1);
	exec_pipex(info, cmd_list, &status);
	exit(WEXITSTATUS(status));
}
