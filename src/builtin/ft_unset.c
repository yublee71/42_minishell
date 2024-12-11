/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:55:17 by tikochoi          #+#    #+#             */
/*   Updated: 2024/12/11 00:50:28 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	unset_arg(char *arg, t_env **env_lst)
{
	size_t	len;
	t_env	*current;
	t_env	*previous;

	len = ft_strlen(arg);
	current = *env_lst;
	previous = NULL;
	while (current)
	{
		if (len == ft_strlen(current->name)
			&&!ft_strncmp(arg, current->name, len))
		{
			if (previous)
				previous->next = current->next;
			else
				*env_lst = current->next;
			free(current->name);
			free(current->var);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

int	ft_unset(char **args, t_env **env_lst)
{
	int		i;

	i = 0;
	while (args[++i])
		unset_arg(args[i], env_lst);
	return (0);
}
