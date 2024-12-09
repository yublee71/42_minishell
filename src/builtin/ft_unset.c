/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:55:17 by tikochoi          #+#    #+#             */
/*   Updated: 2024/12/09 21:45:37 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	unset_arg(char *arg, t_env **env_lst) //separate a function to avoid more than 25 lines for nominette
{
	size_t	len;
	t_env	*current;//easier to control with one pointer not double
	t_env	*previous;//needed when inserting a list node

	len = ft_strlen(arg);
	current = *env_lst;
	previous = NULL;
	while (current)
	{
		if (len == ft_strlen(current->name) //need to check len first
			&&!ft_strncmp(arg, current->name, len))
		{
			if (previous)
				previous->next = current->next;
			else //when current node was the very first at the list
				*env_lst = current->next; //list starts with the next node
			free(current->name);
			free(current->var);
			free(current);
			return ; //successfully unset, so no need to return any exit code
		}
		previous = current;
		current = current->next;
	}
}

int	ft_unset(char **args, t_env **env_lst)
{
	int		i;

	i = 0;
	while (args[++i]) //looks all the arguments
		unset_arg(args[i], env_lst);
	return (0);
}
