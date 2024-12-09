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
// cd .. == go to 1 step before
// cd absolute path = go to that path
// TODO: error control 
// TODO: set the update the OLDPWD to PWD
//                          PWD to path_to_go 
int	ft_cd(char *path_to_go, t_env **env_lst)
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
		status = change_directory("HOME", env_lst);
	else if (!ft_strncmp(path_to_go, "..", 2))
		status = change_directory("OLDPWD", env_lst);
	else
		status = change_directory(path_to_go, env_lst);
	if (status != 0)
	{
		write(2, "Error: cd\n", ft_strlen("Error: cd\n"));
		return (1);
	}
	return (0);
}
