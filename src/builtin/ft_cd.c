/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:32:39 by tchoi             #+#    #+#             */
/*   Updated: 2024/12/09 01:43:58 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char *ft_get_parent_path(char *str)
{
	int i = 0;
	int last_slash = -1;

	while (str[i])
	{
		if (str[i] == '/')
			last_slash = i;
		i++;
	}
	if (last_slash <= 0)
		return (ft_strdup("/"));
	return (ft_substr(str, 0, last_slash));
}

static void update_pwd(t_env **env_lst)
{
	t_env	*current;
	char	*temp;

	current = *env_lst;
	while (current)
	{
		if (ft_strlen(current->name) == 3
			&& !ft_strncmp(current->name, "PWD", 3))
			break;
		current = current->next;
	}
	temp = current->var;
	current->var = getcwd(NULL, 0);
	free(temp);
}

static int	change_directory(char *path, t_env **env_lst)
{
	char	*path_togo;
	int		status;
	t_env	*current;

	current = *env_lst;
	status = 1;
	while (current)
	{
		if (ft_strlen(current->name) == ft_strlen(path)
			&& !ft_strncmp(current->name, path, ft_strlen(path)))
		{
			if (!ft_strncmp("PWD", path, ft_strlen(path)))
				path_togo = ft_get_parent_path(current->var);
			else
				path_togo = ft_strdup(current->var);
			status = chdir(path_togo);
			update_pwd(env_lst);
			free(path_togo);
			break ;
		}
		current = current->next;
	}
	return (status);
}

static int	change_directory_by_path(char *path, t_env **env_lst)
{
	int		status;

	status = chdir(path);
	update_pwd(env_lst);
	return (status);
}

int	ft_cd(char **args, t_env **env_lst)
{
	int		status;
	char	*path_to_go;
	char	*err_msg;

	if (array_size((void **)args) > 2)
	{
		err_msg = "cd: too many arguments\n";
		write(2, err_msg, ft_strlen(err_msg));
		return (1);
	}
	path_to_go = args[1];
	if (path_to_go == NULL)
		status = change_directory("HOME", env_lst);
	else if (ft_strlen(path_to_go) == 2 && !ft_strncmp(path_to_go, "..", 2))
		status = change_directory("PWD", env_lst);
	else
		status = change_directory_by_path(path_to_go, env_lst);
	if (status != 0)
	{
		write(2, "cd: ", ft_strlen("cd :"));
		write(2, path_to_go, ft_strlen(path_to_go));
		write(2, ": No such file or directory\n",
			ft_strlen(": No such file or directory\n"));
		return (1);
	}
	return (0);
}
