/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 01:19:29 by yublee            #+#    #+#             */
/*   Updated: 2024/08/08 00:25:09 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_isoperater(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

void	remove_quotes(void *content)
{
	t_token	*token;
	char	*tmp;

	token = (t_token *)content;
	if (token->type != TK_WORD)
		return ;
	if (ft_strchr(token->value, '"')
		|| ft_strchr(token->value, '\''))
	{
		tmp = token->value;
		token->value = ft_strtrim(token->value, "\"'");//need to change
		free(tmp);
	}
}

char	*mask_quoted_part(char *s)
{
	char	*s_tmp;
	size_t	i;
	char	quote;

	if (!s)
		return (NULL);
	s_tmp = ft_strdup(s);
	if (!s_tmp)
		exit(EXIT_FAILURE);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			quote = s[i];
			s_tmp[i] = quote;
			while (s[++i] && s[i] != quote)
				s_tmp[i] = quote;
			if (!s[i])
				break;
		}
		i++;
	}
	return (s_tmp);
}
