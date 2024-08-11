/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:40:12 by yublee            #+#    #+#             */
/*   Updated: 2024/08/11 18:42:01 by yublee           ###   ########.fr       */
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

char	*get_path(char *cmd, char **env)
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
