/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoi <tchoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:25:41 by tchoi             #+#    #+#             */
/*   Updated: 2024/08/24 16:01:43 by tchoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"


int		ft_unset(char *name, t_info *info)
{
	int i = 0;
	t_env **env;
	t_env *temp;

	i = ft_strlen(name);
	env = info->env;
	while(*env)
	{
		if(!ft_strncmp(name, (*env)->name, i))
		{
			temp = *env;
			*env = (*env)->next;
			free(temp->name);
			free(temp->var);
			free(temp);
			return (0);
		}
		*env = (*env)->next;	
	}
	return (1);
}