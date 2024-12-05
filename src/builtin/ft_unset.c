/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:55:17 by tikochoi          #+#    #+#             */
/*   Updated: 2024/12/05 02:11:27 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_unset(char *name, t_env **env)
{
	int		i;
	t_env	*temp;
	t_env	**current;

	current = env;
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
