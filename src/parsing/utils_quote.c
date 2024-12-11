/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 01:19:29 by yublee            #+#    #+#             */
/*   Updated: 2024/12/08 03:35:07 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*copy_except_quotes(char *str)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	len;
	char	quote;

	new = (char *)ft_calloc(ft_strlen(str) + 1, 1);
	i = 0;
	j = 0;
	while (str[i] && new)
	{
		while (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			len = 0;
			while (str[++i] && str[i] != quote)
				len++;
			ft_strncpy(new + j, str + i - len, len);
			if (!str[i++] || !str[i])
				return (new);
			j += len;
		}
		new[j++] = str[i++];
	}
	return (new);
}

void	remove_quotes(void *content)
{
	t_token	*token;
	char	*str;
	char	*new;

	token = (t_token *)content;
	if (!token || !token->value
		|| (token->type != TK_WORD && token->type != TK_FILE))
		return ;
	str = token->value;
	if (ft_strchr(str, '"') || ft_strchr(str, '\''))
	{
		new = copy_except_quotes(str);
		if (!new)
			exit(EXIT_FAILURE);
		free(str);
		token->value = new;
	}
}

char	*mask_single_quoted_part(char *s)
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
	while (s[0] != '\"' && s[i])
	{
		if (s[i] == '\'')
		{
			quote = s[i];
			s_tmp[i] = quote;
			while (s[++i] && s[i] != quote)
				s_tmp[i] = quote;
			if (!s[i])
				break ;
		}
		i++;
	}
	return (s_tmp);
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
				break ;
		}
		i++;
	}
	return (s_tmp);
}
