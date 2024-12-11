/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:55:53 by yublee            #+#    #+#             */
/*   Updated: 2024/12/10 21:15:38 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_before_exit(t_info *info, int is_parent_process)
{
	if (info->fds)
		free_array_until((void **)info->fds, info->cmd_cnt - 1);
	if (info->root)
		ast_apply_suffix(info->root, ast_free_node);
	if (info->env_lst && !is_parent_process)
		free_env(info->env_lst);
}

void	exit_with_message(char *str, int exit_no, t_info *info)
{
	char	*err_msg;

	if (str && exit_no == 127)
	{
		err_msg = ": command not found\n";
		write(2, str, ft_strlen(str));
		write(2, err_msg, ft_strlen(err_msg));
	}
	else if (str && exit_no == 126)
	{
		err_msg = ": Is a directory\n";
		write(2, str, ft_strlen(str));
		write(2, err_msg, ft_strlen(err_msg));
	}
	else if (str)
		write(2, str, ft_strlen(str));
	else if (!str && errno)
		perror(NULL);
	free_before_exit(info, 0);
	exit(exit_no);
}
