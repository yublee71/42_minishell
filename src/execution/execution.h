/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:35:08 by yublee            #+#    #+#             */
/*   Updated: 2024/12/09 18:03:56 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../../include/minishell.h"

void	child_process(int i, t_ast *cmd_node, t_info *info);
void	exec_builtin(t_ast *cmd_node, t_info *info);
void	set_stdin(int i, t_ast *cmd, t_info *info);
void	handle_heredoc_input(char *delimiter, t_info *info);
void	set_stdout(int i, t_ast *cmd, t_info *info);

#endif