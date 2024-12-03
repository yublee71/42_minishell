/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:18:48 by yublee            #+#    #+#             */
/*   Updated: 2024/12/03 19:23:20 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

//TODO: modify
int	call_builtin(int argc, char **argv, char **env) // combine to the set up function, should be ready when first start the shell
{
	int		env_count;
	t_env	**env_arr;

	env_count = ft_count_env(env);
	env_arr = malloc(sizeof(t_env *) * env_count);
	ft_initenv(env, env_arr);
	//t_env *temp = *env_arr;
	//while (temp)
	//{
	//	printf("%s=%s\n", temp->name, temp->var);
	//	temp = temp->next;
	//}
	ft_unset("PWD", env_arr);
	//temp = *env_arr;
	//while (temp) 
	//{
	//	printf("%s=%s\n", temp->name, temp->var);
	//	temp = temp->next;
	//}
	free(env_arr); // Free the array itself
}