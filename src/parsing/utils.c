/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 01:19:29 by yublee            #+#    #+#             */
/*   Updated: 2024/08/07 02:32:51 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_isoperater(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

void	remove_quotes(void *content)
{
	t_token			*token;

	token = (t_token *)content;
	(void)token;
}

char	*mask_quoted_part(char *s)
{
	char	*s_tmp;
	size_t	i;
	char	quote;

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
			s_tmp[i] = quote;
		}
		i++;
	}
	return (s_tmp);
}
