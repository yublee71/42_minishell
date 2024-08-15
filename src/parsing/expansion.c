/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:29:35 by yublee            #+#    #+#             */
/*   Updated: 2024/08/15 15:26:32 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// static char	*remove_paired_quotes(char *str)
// {
// 	char	*new;
// 	char	quote;
// 	size_t	i;
// 	size_t	j;

// 	new = ft_strdup(str);
// 	if (!new)
// 		exit(EXIT_FAILURE);
// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' || str[i] == '"')
// 		{
// 			quote = str[i++];
// 			while (str[i] != quote)
// 				new[j++] = str[i++];
// 			i++;
// 		}
// 		else
// 			new[j++] = str[i++];
// 	}
// 	while (j < ft_strlen(str) + 1)
// 		new[j++] = 0;
// 	return (new);
// }
static char	*expand_if_dollar_sign(char *value, char **env)
{
	char	*str;

	(void)env;
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
void	expand_env_var(t_list *token_list, char **env)
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
			token->value = expand_if_dollar_sign(token->value, env);
			free(tmp);
		}
		node = node->next;
	}
}
