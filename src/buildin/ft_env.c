/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoi <tchoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 14:19:31 by tchoi             #+#    #+#             */
/*   Updated: 2024/08/24 16:02:36 by tchoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

int		ft_env(t_info *info)
{
	int		i;
	t_env	**env;

	i = 0;
	env = info->env;
	if(!*env || !env)
			exit_with_message("env", EXIT_FAILURE, info);
	while(*env)
	{
		ft_printf("%s=%s\n", (*env)->name, (*env)->var);
		*env = (*env)->next;
	}
	return(0);
}