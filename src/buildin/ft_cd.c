/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoi <tchoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:54:16 by tchoi             #+#    #+#             */
/*   Updated: 2024/08/24 17:14:14 by tchoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

static int	change_directory(char *path, t_info *info)
{
	int i = 0;
	char *path_togo;
	int status;
	t_env **env;

	env = info->env;
	if (!ft_strncmp(path, "OLDPWD", 6) || !ft_strncmp(path, "HOME", 4)) //if user wants to go to previous dir (cd ..) or home (cd )
	{
		while (*env) //look for the name in the env arr
		{
			if (!ft_strncmp((*env)->name, path, ft_strlen(path)))
			{
				path_togo = (*env)->var;
				status = chdir(path_togo);
				ft_update_env(path_togo, info);
				return (status);
			}
			*env = (*env)->next;
		}
	}
	else 
	{
		status = chdir(path);
		ft_update_env(path, info);
	}
	return (status);
}

static void	ft_update_env(char *path, t_info *info)
{
	t_env **env;
	char *path_str;
	char *pwd;
	char *oldpwd;

	path_str = malloc(sizeof(char) * (ft_strlen(path) + 1));
	if (!path_str)
		exit_with_message("malloc", EXIT_FAILURE, info);
	path_str = ft_strdup(path);
	pwd = ft_find_update_env("PWD", &path_str, info); 
	oldpwd = ft_find_update_env("OLDPWD", &pwd, info);
	if (!pwd || !oldpwd)
		exit_with_message("env", EXIT_FAILURE, info);
	free(oldpwd);
}


static char	*ft_find_update_env(char *path_to_find, char **path_to_update, t_info *info)
{
	t_env **env;
	char *temp;

	env = info->env;
	while(*env)
	{
		if (!ft_strncmp((*env)->name, path_to_find, ft_strlen(path_to_find)))
		{
			temp = (*env)->var;
			(*env)->var = path_to_update;
			return (temp);
		}
		*env = (*env)->next;
	}
	return (NULL);
}

// cd  == go back HOME
// cd .. == go to OLDPWD
// cd absolute path = go to that path
// set the update the OLDPWD == PWD
//                       PWD == path_to_go 
int		ft_cd(char *path_to_go, t_info *info)
{
	int		status;

	if(path_to_go == NULL)
		status = change_directory("HOME", info);
	else if (!ft_strncmp(path_to_go, "..", 2))
		status = change_directory("OLDPWD", info);
	else
		status = change_directory(path_to_go, info);
	if (status != 0)
		exit_with_message("cd", EXIT_FAILURE, info);
	return(0);
}