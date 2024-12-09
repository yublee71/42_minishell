/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 01:29:40 by yublee            #+#    #+#             */
/*   Updated: 2024/12/09 02:49:19 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	exec_builtin(t_ast *cmd_node, t_info *info)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
		exit_with_message("dup", EXIT_FAILURE, info);
	set_stdin(-1, cmd_node, info); // TODO: handle non-existing files
	set_stdout(-1, cmd_node, info);
	*(info->status) = call_builtin(cmd_node->args, info);
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		exit_with_message("dup2", EXIT_FAILURE, info);
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		exit_with_message("dup2", EXIT_FAILURE, info);
}
