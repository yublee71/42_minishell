/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:32:39 by tchoi             #+#    #+#             */
/*   Updated: 2024/12/05 02:10:01 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*ft_strdup_from(const char *s, int start)
{
	int		i;
	int		count;
	char	*arr;

	i = 0;
	count = 0;
	if (!s[start]) // str is shorter than the index to start dup from e.g. *s = hello, start = 7
		return (NULL);
	while (s[count])
		count++;
	arr = malloc((count - start + 1) * sizeof(char));
	if (arr == NULL)
		return (NULL);
	while (start < count)
	{
		arr[i] = s[start];
		start++;
		i++;
	}
	arr[i] = 0;
	return (arr);
}

static int	change_directory(char *path, char **env)
{
	int		i;
	char	*path_togo;
	int		status;

	i = 0;
	if (!ft_strncmp(path, "OLDPWD=", 7) || !ft_strncmp(path, "HOME=", 5))
	{
		while (env[i])
		{
			if (!ft_strncmp(env[i], path, ft_strlen(path)))
			{
				path_togo = ft_strdup_from(env[i], ft_strlen(path));
				status = chdir(path_togo);
				return (status);
			}
			i++;
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
int	ft_cd(char *path_to_go, char **env)
{
	int	status;

	if (path_to_go == NULL)
		status = change_directory("HOME=", env);
	else if (!ft_strncmp(path_to_go, "..", 2))
		status = change_directory("OLDPWD=", env);
	else
		status = change_directory(path_to_go, env);
	if (status != 0)
	{
		printf("Error: cd\n");
		exit(1);
	}
	return (0);
}
