/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:32:39 by tchoi             #+#    #+#             */
/*   Updated: 2024/12/05 02:43:04 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	change_directory(char *path, t_env **env)
{
	char	*path_togo;
	int		status;
	t_env	*current;

	current = *env;
	while (current)
	{
		if (ft_strlen(current->name) == ft_strlen(path)
			&& !ft_strncmp(current->name, path, ft_strlen(path)))
		{
			path_togo = current->var;
			status = chdir(path_togo);
			return (status);
		}
		current = current->next;
	}
	status = chdir(path);
	return (status);
}

// cd  == go back HOME
// cd .. == go to OLDPWD
// cd absolute path = go to that path
// TODO: error control 
// TODO: set the update the OLDPWD to PWD
//                          PWD to path_to_go 
int	ft_cd(char *path_to_go, t_env **env)
{
	int		status;
	// t_env	*current;

	// printf("to go:%s\n", path_to_go);
	// current = *env;
	// while (current)
	// {
	// 	printf("name:%s\n",current->name);
	// 	printf("val:%s\n",current->var);
	// 	current = current->next;
	// }
	if (path_to_go == NULL)
		status = change_directory("HOME", env);
	else if (!ft_strncmp(path_to_go, "..", 2))
		status = change_directory("OLDPWD", env);
	else
		status = change_directory(path_to_go, env);
	if (status != 0)
	{
		printf("Error: cd\n");
		return (1);
	}
	return (0);
}
