/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:55:17 by tikochoi          #+#    #+#             */
/*   Updated: 2024/12/08 00:58:19 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_unset(char *name, t_env **env_lst)
{
	int		i;
	t_env	*temp;
	t_env	**current;

	current = env_lst;
	i = ft_strlen(name);
	while (*current)
	{
		if (!ft_strncmp(name, (*current)->name, i)) // matched
		{
			temp = *current;
			*current = (*current)->next;
			free(temp->name);
			free(temp->var);
			free(temp);
			return (1);
		}
		current = &(*current)->next;
	}
	return (0);
}
