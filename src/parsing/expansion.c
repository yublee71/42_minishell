/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:29:35 by yublee            #+#    #+#             */
/*   Updated: 2024/08/09 03:35:01 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*expand_if_dollar_sign(char *value, char **env)
{
	(void)env;
	char	*str;

	if (!ft_strchr(value, '$'))
	{
		str = ft_strdup(value);
		if (!str)
			exit(EXIT_FAILURE);
	}
	else
	{
		str = NULL;//need to change
	}
	return (str);
}
//mask only single quote
void	expand_env_var(t_list *token_list, char **env)
{
	t_list	*node;
	t_token	*token;
	char	*tmp;
	// char	*str;

	if (!token_list)
		return;
	node = token_list;
	while (node)
	{
		token = (t_token *)node->content;
		if (ft_strchr(token->value, '"'))
		{
			tmp = token->value;
			token->value = expand_if_dollar_sign(token->value, env);
			free(tmp);
		}
		node = node->next;
	}
}
