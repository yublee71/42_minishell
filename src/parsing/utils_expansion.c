/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:05:34 by yublee            #+#    #+#             */
/*   Updated: 2024/12/09 21:14:14 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	count_name_len(char *str, size_t i)
{
	size_t	name_len;

	name_len = 0;
	while (str[i + name_len] && !isspace(str[i + name_len])
		&& str[i + name_len] != '\'' && str[i + name_len] != '\"')
		name_len++;
	return (name_len);
}

t_env	*search_name_in_env(t_env **env_lst, size_t name_len, char *str)
{
	t_env	*current;

	current = *env_lst;
	while (current)
	{
		if (name_len == ft_strlen(current->name)
			&& !ft_strncmp(str, current->name, name_len))
			break ;
		current = current->next;
	}
	return (current);
}
