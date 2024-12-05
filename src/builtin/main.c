/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:18:48 by yublee            #+#    #+#             */
/*   Updated: 2024/12/05 04:06:29 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// //TODO: modify
int	call_builtin(char **args, t_info *info) // combine to the set up function, should be ready when first start the shell
{
	int	i;
	int	status;

	i = is_builtin(args[0]);
	status = -1;
	if (i == 0)
		status = ft_cd(args[1], info->env_lst);
	else if (i == 1)
		status = ft_echo(args[1]);
	else if (i == 2)
		status = ft_export(info->env);
	else if (i == 3)
		status = ft_pwd();
	else if (i == 4)
		status = ft_unset(args[1], info->env_lst);
	return (status);
	//t_env *temp = *env_arr;
	//while (temp)
	//{
	//	printf("%s=%s\n", temp->name, temp->var);
	//	temp = temp->next;
	//}
	// ft_unset("PWD", env_arr);
	//temp = *env_arr;
	//while (temp) 
	//{
	//	printf("%s=%s\n", temp->name, temp->var);
	//	temp = temp->next;
	//}
	// free(env_arr); // Free the array itself
}
