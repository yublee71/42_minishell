/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:32:39 by tchoi             #+#    #+#             */
/*   Updated: 2024/12/03 19:20:49 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static t_env *ft_get_env(char *name_look_for, t_env **env_arr) //retrieve the env by compare the name
{
	t_env	**current;
	int len;

	current = env_arr;
	len = ft_strlen(name_look_for);
	while(*current)
	{
		if(!ft_strncmp(name_look_for, (*current)->name, len))
			return (*current);
		current = &(*current)->next;
	}
	return (NULL);
}

static char *ft_get_parent_path(t_env **env_arr) //for cd .., return to the path above the current one, not oldpwd
{
	t_env	**current;
	t_env *current_pwd;
	int i;
	int	last_slash;
	char	*parentpath;

	i = 0;
	current = env_arr;
	current_pwd = ft_get_env("PWD", current);
	while(current_pwd->var[i])
	{
		if(current_pwd->var[i] == '/')
			last_slash = i;
		i++;
	}
	parentpath = ft_substr(current_pwd->var, 0, last_slash);
	return(parentpath);
}

static int change_directory(char *path, t_env **env_arr)
{
    t_env *current_pwd;
    t_env *old_pwd;
    int status;

    current_pwd = ft_get_env("PWD", env_arr);
    old_pwd = ft_get_env("OLDPWD", env_arr);
    status = chdir(path);
    if (status)
    {
        printf("Error: cd path not found\n");
        return status;
    }
    if (current_pwd && old_pwd)
    {
        free(old_pwd->var);
        old_pwd->var = ft_strdup(current_pwd->var); 
        free(current_pwd->var);
        current_pwd->var = ft_strdup(path);
    }
    return status;
}


static char	*ft_join_env(char *argu, t_env **env_arr)
{
	t_env	**current;
	t_env	*current_pwd;
	char	*fullpath;
    char    *path_slash;

	current = env_arr;
	current_pwd = ft_get_env("PWD", current);
    path_slash = ft_strjoin(current_pwd->var, "/\0");
	fullpath = ft_strjoin(path_slash, argu);
    free(path_slash);
	return(fullpath);
}

// cd  == go back HOME
// cd .. == go to 1 step before
// cd absolute path = go to that path
// TODO: error control 
// TODO: set the update the OLDPWD to PWD
//                          PWD to path_to_go 
int ft_cd(int argc, char **argv, t_env **env_arr)
{
    int status;
    char *path_togo;
    t_env *home_env;

    if (argc == 1) 
    {
        home_env = ft_get_env("HOME", env_arr);
        if (!home_env || !home_env->var) 
        {
            printf("Error: HOME not set\n");
            return -1;
        }
        path_togo = home_env->var;
        status = change_directory(path_togo, env_arr);
    } 
    else if (argc == 2) 
    {
        if (!ft_strncmp(argv[1], "..", 2))
            path_togo = ft_get_parent_path(env_arr);
        else

            path_togo = ft_join_env(argv[1], env_arr);
        if (!path_togo) 
        {
            printf("Error: Unable to determine path\n");
            return -1;
        }
        status = change_directory(path_togo, env_arr);
        free(path_togo);
    } 
    else 
    {
        printf("Error: cd too many arguments\n");
        return -1;
    }
    return (status);
}