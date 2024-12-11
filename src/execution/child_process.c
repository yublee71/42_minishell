/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:34:13 by yublee            #+#    #+#             */
/*   Updated: 2024/12/11 17:30:27 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

static char	*get_cmd_path(char *cmd, t_info *info)
{
	char	*path;
	char	**paths;
	char	*cmd_path;
	int		i;

	i = 0;
	if (cmd[0] == '.' || cmd[0] == '/' || !*info->env_lst)
		return (cmd);
	while (!ft_strnstr(info->env[i], "PATH=", 5))
		i++;
	path = ft_strnstr(info->env[i], "PATH=", 5) + 5;
	paths = ft_split(path, ':');
	cmd_path = join_cmd_to_path(cmd, paths);
	free_array((void **)paths);
	return (cmd_path);
}

static void	handle_error_case(char *cmd_path, t_info *info)
{
	if (errno == 13)
		exit_with_message(NULL, 126, info);
	else if (cmd_path[0] == '.' || cmd_path[0] == '/')
		exit_with_message(NULL, 127, info);
	else
		exit_with_message(cmd_path, 127, info);
}

void	child_process(int i, t_ast *cmd_node, t_info *info)
{
	char		**args;
	char		*cmd_path;
	struct stat	path_stat;

	set_stdin(i, cmd_node, info);
	set_stdout(i, cmd_node, info);
	if (g_sigint_received)
		exit_with_message(NULL, EXIT_SUCCESS, info);
	args = cmd_node->args;
	if (args == NULL || !ft_strlen(args[0]))
		exit_with_message(NULL, EXIT_SUCCESS, info);
	if (which_builtin(args[0]) >= 0)
		exit_with_message("", call_builtin(cmd_node->args, info), info);
	cmd_path = get_cmd_path(args[0], info);
	if ((ft_strlen(cmd_path) == 1 && cmd_path[0] == '.')
		|| (ft_strlen(cmd_path) == 2 && !ft_strncmp(cmd_path, "..", 2)))
		exit_with_message("filename argument required\n", 2, info);
	if (access(cmd_path, X_OK) < 0)
		handle_error_case(cmd_path, info);
	if (!stat(cmd_path, &path_stat) && S_ISDIR(path_stat.st_mode))
		exit_with_message(cmd_path, 126, info);
	if (execve(cmd_path, args, environ) == -1)
		exit_with_message(NULL, EXIT_FAILURE, info);
}
