/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_child_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:34:13 by yublee            #+#    #+#             */
/*   Updated: 2024/08/09 04:18:32 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(int i, t_list *current, t_info info)
{
	t_ast	*cmd;
	char	*cmd_str;
	char	*tmp;
	char	**argv;

	cmd = (t_ast *)current->content;
	get_input(cmd, i, info);
	get_output(cmd, i, info);
	cmd_str = cmd->item;
	if (cmd_str[0] == 0)
		exit_with_message(NULL, EXIT_SUCCESS, info);
	argv = get_argv(cmd_str, info.env);
	if (access(argv[0], X_OK))
	{
		tmp = ft_strdup(argv[0]);
		free_str_array(argv);
		exit_with_message(tmp, 127, info);
	}
	if (execve(argv[0], argv, info.env) == -1)
	{
		free_str_array(argv);
		exit_with_message("execve", EXIT_FAILURE, info);
	}
}
