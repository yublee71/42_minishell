/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:09:30 by tikochoi          #+#    #+#             */
/*   Updated: 2024/12/08 03:36:55 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_env(t_info *info)
{
	t_env	*current;

	current = *(info->env_lst);
	if (!current)
		exit_with_message("env", EXIT_FAILURE, info);
	while (current)
	{
		ft_printf("%s=%s\n", current->name, current->var);
		current = current->next;
	}
	return (0);
}
