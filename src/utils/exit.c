/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:55:53 by yublee            #+#    #+#             */
/*   Updated: 2024/12/05 04:01:42by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_before_exit(t_info	*info)
{
	if (info->fds)
		free_array_until((void **)info->fds, info->cmd_cnt - 1);
	if (info->root)
		ast_apply_suffix(info->root, ast_free_node);
	if (info->env_lst)
		free_env(info->env_lst);
}

void	exit_with_message(char *str, int exit_no, t_info *info)
{
	if (str)
	{
		if (exit_no == 127)
		{
			write(2, str, ft_strlen(str));
			write(2, ": command not found\n", 20);
		}
		else if (exit_no)
			perror(str);
	}
	free_before_exit(info);
	exit(exit_no);
}
