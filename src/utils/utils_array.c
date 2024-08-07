/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:41:06 by yublee            #+#    #+#             */
/*   Updated: 2024/08/06 20:27:21 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	array_size(void **arr)
{
	int	i;

	if (!arr)
		return (-1);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

t_list	**array_to_list(void **arr)
{
	t_list	*head;
	t_list	*new;
	int		i;

	if (!arr)
		return (NULL);
	i = 0;
	if (arr[i])
	{
		head = ft_lst_new((void *)arr[i++]);
		if (!head)
			exit(EXIT_FAILURE);
	}
	while (arr[i])
	{
		new = ft_lst_new((void *)arr[i]);
		if (!new)
			exit(EXIT_FAILURE);
		ft_lstadd_back(&head, new);
		i++;
	}
	return (&head);
}

void	free_array(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}