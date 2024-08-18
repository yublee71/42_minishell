/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoi <tchoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:54:16 by tchoi             #+#    #+#             */
/*   Updated: 2024/08/18 12:05:09 by tchoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

int change_directory(char *path, t_env **env)
{
    int i = 0;
    char *path_togo;
    int status;

    if (!ft_strncmp(path, "OLDPWD", 6) || !ft_strncmp(path, "HOME", 4)) //if user wants to go to previous dir (cd ..) or home (cd )
    {
        while (*env) //look for the name in the env arr
        {
            if (!ft_strncmp((*env)->name, path, ft_strlen(path)))
            {
                path_togo = (*env)->var;
                status = chdir(path_togo);
                return (status);
            }
            *env = (*env)->next;
        }
    }
    else 
        status = chdir(path);
    return (status);
}


// cd  == go back HOME
// cd .. == go to OLDPWD
// cd absolute path = go to that path
// TODO: error control 
// TODO: set the update the OLDPWD to PWD
//                          PWD to path_to_go 
int ft_cd(char *path_to_go, t_info *info)
{
    int status;

    if(path_to_go == NULL)
        status = change_directory("HOME", info->env);
    else if (!ft_strncmp(path_to_go, "..", 2))
        status = change_directory("OLDPWD", info->env);
    else
        status = change_directory(path_to_go, info->env);
    if (status != 0)
        exit_with_message("cd", EXIT_FAILURE, info);
    return(0);
}