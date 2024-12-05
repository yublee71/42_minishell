/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:18:48 by yublee            #+#    #+#             */
/*   Updated: 2024/12/05 02:52:19 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// //TODO: modify
int	call_builtin(char **args, t_info *info) // combine to the set up function, should be ready when first start the shell
{
	int		i;

	i = is_builtin(args[0]);
	if (i == 0)
		return (ft_cd(args[1], info->env_arr));
	else if (i == 1)
		return (ft_echo(args[1]));
	else if (i == 2)
		return (ft_export(info->env));
	else if (i == 3)
		return (ft_pwd());
	else if (i == 4)
		return (ft_unset(args[1], info->env_arr));
	else
		return (-1);
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
