/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:18:48 by yublee            #+#    #+#             */
/*   Updated: 2024/12/09 18:51:01 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	call_builtin(char **args, t_info *info) // combine to the set up function, should be ready when first start the shell
{
	int	i;
	int	status;

	i = which_builtin(args[0]);
	status = -1;
	if (i == 0)
		status = ft_cd(args[1], info->env_lst);
	else if (i == 1)
		status = ft_echo(args);
	else if (i == 2)
		status = ft_env(info);
	else if (i == 3)
		status = ft_exit(args, info);
	else if (i == 4)
		status = ft_export(info->env);
	else if (i == 5)
		status = ft_pwd();
	else if (i == 6)
		status = ft_unset(args[1], info->env_lst);
	return (status);
}
