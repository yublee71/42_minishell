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
    // char *parentpath;

    while (str[i])
    {
        if (str[i] == '/')
            last_slash = i;
        i++;
    }
    if (last_slash <= 0) // Root or no slash
        return (ft_strdup("/"));
    return (ft_substr(str, 0, last_slash));
}

// static void update_env(char *new_path, t_env **env_lst)
// {
//     t_env *current = *env_lst;
//     t_env *temp_pwd = NULL;
//     t_env *temp_oldpwd = NULL;

//     while (current)
//     {
//         if (ft_strncmp(current->name, "PWD") == 0)
//             temp_pwd = current;
//         else if (ft_strncmp(current->name, "OLDPWD") == 0)
//             temp_oldpwd = current;
//         current = current->next;
//     }
//     if (temp_pwd && temp_oldpwd)
//     {
//         free(temp_oldpwd->var);
//         temp_oldpwd->var = ft_strdup(temp_pwd->var); 
//         free(temp_pwd->var);
//         temp_pwd->var = ft_strdup(new_path);
//     }
// }

static int	change_directory(char *path, t_env **env_lst)
{
	char	*path_togo;
	int		status;
	t_env	*current;

	current = *env_lst;
	while (current)
	{
		if (ft_strlen(current->name) == ft_strlen(path)
			&& !ft_strncmp(current->name, path, ft_strlen(path)))
		{
			if (!ft_strncmp("PWD", path, ft_strlen(path))) //return to previous page
				path_togo = ft_get_parent_path(current->var);
			else
				path_togo = current->var; //go bach "HOME"
			status = chdir(path_togo);
			return (status);
		}
		current = current->next;
	}
	status = chdir(path);
	return (status);
}

// cd  == go back HOME
// cd .. == go to 1 step before
// cd absolute path = go to that path
// TODO: error control 
// TODO: set the update the OLDPWD to PWD
//                          PWD to path_to_go 
int	ft_cd(char **args, t_env **env_lst)
{
	int		status;
	char	*path_to_go;
	// t_env	*current;

	// printf("to go:%s\n", path_to_go);
	// current = *env;
	// while (current)
	// {
	// 	printf("name:%s\n",current->name);
	// 	printf("val:%s\n",current->var);
	// 	current = current->next;
	// }
	if (array_size((void **)args) != 2)
	{
		write(2, "cd: too many arguments\n", ft_strlen("cd: too many arguments\n"));
		return (1);
	}
	path_to_go = args[1];
	if (path_to_go == NULL)
		status = change_directory("HOME", env_lst);
	else if (!ft_strncmp(path_to_go, "..", 2))
		status = change_directory("PWD", env_lst); //based on PWD, find the parents path
	else
		status = change_directory(path_to_go, env_lst);
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
