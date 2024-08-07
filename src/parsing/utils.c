/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 01:19:29 by yublee            #+#    #+#             */
/*   Updated: 2024/08/07 02:01:22 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_isoperater(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->value);
	free(token);
}

void	print_token(void *content)
{
	t_token			*token;
	const char		*type_names[8] = {
		"WORD", "PIPE", "INPUT", "OUTPUT", "APPEND",
		"HEREDOC", "SQUOTE", "DQUOTE"};
	int				type;
	int				type_val;
	int				i;

	token = (t_token *)content;
	ft_printf("val: \"%s\"\n", token->value);
	type = token->type;
	i = 0;
	type_val = 1;
	while (!(type == type_val))
	{
		type_val = type_val << 1;
		i++;
	}
	ft_printf("type: %s\n", type_names[i]);
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
