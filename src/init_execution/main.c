/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 23:32:48 by yublee            #+#    #+#             */
/*   Updated: 2024/08/15 23:46:48 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static int	**create_pipeline(int cnt)
{
	int	**fds;
	int	i;

	if (cnt <= 0)
		return (NULL);
	fds = (int **)malloc(cnt * sizeof(int *));
	if (!fds)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < cnt)
	{
		fds[i] = malloc(2 * sizeof(int));
		if (!fds[i])
		{
			free_array_until((void **)fds, i);
			exit(EXIT_FAILURE);
		}
		if (pipe(fds[i]) < 0)
		{
			free_array_until((void **)fds, i + 1);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (fds);
}

static int	count_pipe(t_ast *root)
{
	int		cnt;
	t_ast	*current;

	if (!root)
		return (-1);
	cnt = 0;
	if (root->type == TK_PIPE)
	{
		cnt++;
		current = root->right;
		while (current && current->type == TK_PIPE)
		{
			cnt++;
			current = current->right;
		}
	}
	return (cnt);
}

t_info	init_executor(t_ast *root, char **env)
{
	t_info	info;
	int		pipe_cnt;
	int		env_count;
	t_env		**env_arr;
	
	env_count = ft_count_env(env); // maybe can be function array_size?
	env_arr = malloc(sizeof(t_env *)* env_count);
	/*if (!env_arr)
		return(NULL);*/
	ft_initenv(env, env_arr);
	info.env = env_arr;
	info.root = root;
	pipe_cnt = count_pipe(root);
	info.cmd_cnt = pipe_cnt + 1;
	info.fds = create_pipeline(pipe_cnt);
	return (info);
}
