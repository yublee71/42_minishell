/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:55:17 by tikochoi          #+#    #+#             */
/*   Updated: 2024/12/03 19:51:01 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static t_env	*ft_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

int	ft_unset(char *name, t_env **env_arr)
{
	int		i;
	t_env	*temp;
	t_env	**current;

	current = env_arr;
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
