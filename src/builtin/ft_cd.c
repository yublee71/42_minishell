/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:32:39 by tchoi             #+#    #+#             */
/*   Updated: 2024/12/11 19:01:40 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*ft_get_parent_path(char *str)
{
	int	i;
	int	last_slash;

	i = 0;
	last_slash = -1;
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

static void	update_pwd(t_env **env_lst)
{
	t_env	*current;
	char	*temp;

	current = *env_lst;
	while (current)
	{
		if (ft_strlen(current->name) == 3
			&& !ft_strncmp(current->name, "PWD", 3))
			break ;
		current = current->next;
	}
	if (current)
	{
		temp = current->var;
		current->var = getcwd(NULL, 0);
		free(temp);
	}
}

static void	update_oldpwd(t_env **env_lst, char *current_path)
{
	t_env	*current;
	char	*temp;

	current = *env_lst;
	while (current)
	{
		if (ft_strlen(current->name) == 6
			&& !ft_strncmp(current->name, "OLDPWD", 6))
			break ;
		current = current->next;
	}
	if (current)
	{
		temp = current->var;
		current->var = current_path;
		free(temp);
	}
}

static int	change_directory(int w_case, char *path, t_env **env_lst)
{
	int		status;
	char	*current_path;
	t_env	*env;

	current_path = getcwd(NULL, 0);
	if (w_case == 1)
	{
		env = find_name_in_env("HOME", 4, env_lst);
		if (!env)
			path = "";
		else
			path = env->var;
		status = chdir(path);
	}
	else if (w_case == 2)
	{
		path = ft_get_parent_path(current_path);
		status = chdir(path);
		free(path);
	}
	else
		status = chdir(path);
	update_pwd(env_lst);
	update_oldpwd(env_lst, current_path);
	return (status);
}

int	ft_cd(char **args, t_info *info)
{
	int		status;
	int		which_case;
	char	*path_to_go;

	if (!*info->env_lst)
		return (0);
	if (array_size((void **)args) > 2)
	{
		write(2, "cd: too many arguments\n", 23);
		return (1);
	}
	path_to_go = args[1];
	which_case = 0;
	if (path_to_go == NULL)
		which_case = 1;
	else if (ft_strlen(path_to_go) == 2 && !ft_strncmp(path_to_go, "..", 2))
		which_case = 2;
	status = change_directory(which_case, path_to_go, info->env_lst);
	if (status != 0 && path_to_go)
	{
		write(2, path_to_go, ft_strlen(path_to_go));
		write(2, ": No such file or directory\n", 28);
		return (1);
	}
	return (0);
}
