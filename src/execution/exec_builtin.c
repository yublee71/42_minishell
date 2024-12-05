/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 01:29:40 by yublee            #+#    #+#             */
/*   Updated: 2024/12/05 02:53:16 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	exec_builtin(t_ast *cmd_node, t_info *info)
{
	set_stdin(-1, cmd_node, info);
	set_stdout(-1, cmd_node, info);
	call_builtin(cmd_node->args, info);
}