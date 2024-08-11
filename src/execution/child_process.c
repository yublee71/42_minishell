/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:34:13 by yublee            #+#    #+#             */
/*   Updated: 2024/08/11 18:39:15 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// static int	is_builtin(char *cmd)
// {
// 	static char	*builtins[5] = {"pwd", "env", "cd", "export", "unset"};
// 	int			i;
// 	char		*str;

// 	//needs to add echo later
// 	i = -1;
// 	while (++i < 5)
// 		if (!ft_strncmp(builtins[i], cmd, ft_strlen(str)))
// 			return (1);
// 	return (0);
// }

void	child_process(int i, t_ast *cmd_node, t_info *info)
{
	char	**args;
	char	*cmd_path;

	get_input(i, cmd_node, info);
	get_output(i, cmd_node, info);
	args = cmd_node->args;
	if (args == NULL)
		exit_with_message(NULL, EXIT_SUCCESS, info);
	// if (is_builtin(args[0]))
	// 	exec_builtin(args, info);
	cmd_path = get_path(args[0], info->env);
	if (access(cmd_path, X_OK) < 0)
		exit_with_message(args[0], 127, info);
	if (execve(cmd_path, args, info->env) == -1)
		exit_with_message("execve", EXIT_FAILURE, info);
}
