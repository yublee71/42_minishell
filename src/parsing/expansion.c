/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:29:35 by yublee            #+#    #+#             */
/*   Updated: 2024/12/08 00:58:30 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*expand_if_dollar_sign(char *value, t_env **env_lst)
{
	char	*str;

	(void)env_lst;
	if (!ft_strchr(value, '$'))
	{
		str = ft_strdup(value);
		if (!str)
			exit(EXIT_FAILURE);
	}
	else
	{
		str = NULL;//TODO: create function
	}
	return (str);
}

//mask only single quote
void	expand_env_var(t_list *token_list, t_env **env_lst)
{
	t_list	*node;
	t_token	*token;
	char	*tmp;

	if (!token_list)
		return ;
	node = token_list;
	while (node)
	{
		token = (t_token *)node->content;
		if (ft_strchr(token->value, '"'))
		{
			tmp = token->value;
			token->value = expand_if_dollar_sign(token->value, env_lst);
			free(tmp);
		}
		node = node->next;
	}
}
