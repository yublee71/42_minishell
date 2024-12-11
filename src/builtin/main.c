/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:18:48 by yublee            #+#    #+#             */
/*   Updated: 2024/12/09 21:26:21 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	which_builtin(char *cmd)
{
	const char	*builtins[7] = {"cd", "echo", "env",
		"exit", "export", "pwd", "unset"};
	int			i;

	i = 0;
	if (!cmd)
		return (-1);
	while (i < 7)
	{
		if (ft_strlen(cmd) == ft_strlen(builtins[i])
			&& !ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i])))
			return (i);
		i++;
	}
	return (-1);
}

int	call_builtin(char **args, t_info *info)
{
	int	i;
	int	status;

	i = which_builtin(args[0]);
	status = -1;
	if (i == 0)
		status = ft_cd(args, info->env_lst);
	else if (i == 1)
		status = ft_echo(args, info);
	else if (i == 2)
		status = ft_env(info);
	else if (i == 3)
		status = ft_exit(args, info);
	else if (i == 4)
		status = ft_export(args, info->env_lst);
	else if (i == 5)
		status = ft_pwd();
	else if (i == 6)
		status = ft_unset(args, info->env_lst);
	return (status);
}
