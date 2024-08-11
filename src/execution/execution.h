/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:35:08 by yublee            #+#    #+#             */
/*   Updated: 2024/08/11 17:41:45 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../../include/minishell.h"

void	child_process(int i, t_ast *cmd_node, t_info *info);
char	*get_path(char *cmd, char **env);
void	get_input(int i, t_ast *cmd, t_info *info);
void	get_output(int i, t_ast *cmd, t_info *info);
void	add_random_str_to_str(char *buf, size_t buf_size, char *str, size_t rand_cnt);
void	exit_with_message(char *str, int exit_no, t_info *info);
void	free_before_exit(t_info	*info);

#endif