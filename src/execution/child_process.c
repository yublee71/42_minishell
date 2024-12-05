/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:34:13 by yublee            #+#    #+#             */
/*   Updated: 2024/12/05 01:40:42 by yublee           ###   ########.fr       */
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

static char	*join_cmd_to_path(char *cmd, char **paths)
{
	int		i;
	char	*temp;
	char	*new;

	i = 0;
	while (paths[i])
	{
		new = ft_strjoin(paths[i], "/");
		if (!new)
			exit(EXIT_FAILURE);
		temp = new;
		new = ft_strjoin(new, cmd);
		if (!new)
			exit(EXIT_FAILURE);
		free(temp);
		if (!access(new, X_OK))
			return (new);
		free(new);
		i++;
	}
	return (cmd);
}

static char	*get_cmd_path(char *cmd, char **env)
{
	char	*path;
	char	**paths;
	char	*cmd_path;
	int		i;

	i = 0;
	while (!ft_strnstr(env[i], "PATH=", 5))
		i++;
	path = ft_strnstr(env[i], "PATH=", 5) + 5;
	paths = ft_split(path, ':');// what if a variable has :?
	cmd_path = join_cmd_to_path(cmd, paths);
	free_array((void **)paths);
	return (cmd_path);
}

void	child_process(int i, t_ast *cmd_node, t_info *info)
{
	char	**args;
	char	*cmd_path;

	set_stdin(i, cmd_node, info);
	set_stdout(i, cmd_node, info);
	if (g_sigint_received)
		exit_with_message(NULL, EXIT_SUCCESS, info);
	args = cmd_node->args;
	if (args == NULL)
		exit_with_message(NULL, EXIT_SUCCESS, info);
	// if (is_builtin(args[0]))
	// 	exec_builtin(args, info);
	cmd_path = get_cmd_path(args[0], info->env);
	if (access(cmd_path, X_OK) < 0)
		exit_with_message(args[0], 127, info);
	if (execve(cmd_path, args, info->env) == -1)
		exit_with_message("execve", EXIT_FAILURE, info);
}
