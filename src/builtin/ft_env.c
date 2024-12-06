/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikochoi <tikochoi@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-06 19:09:30 by tikochoi          #+#    #+#             */
/*   Updated: 2024-12-06 19:09:30 by tikochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		ft_env(t_env **env_arr, t_info *info)
{
	t_env	*current;

	current = env_arr;
	if(!current)
		exit_with_message("env", EXIT_FAILURE, info);
	while(current)
	{
		ft_printf("%s=%s\n", current->name, current->var);
		current = current->next;
	}
	return(0);
}