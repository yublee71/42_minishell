/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 01:19:29 by yublee            #+#    #+#             */
/*   Updated: 2024/08/15 15:27:19 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	count_args(t_list *token_list)
{
	int		cnt;
	t_list	*current;
	t_token	*token;

	cnt = 0;
	current = token_list;
	token = (t_token *)current->content;
	while (current && token->type != TK_PIPE)
	{
		token = (t_token *)current->content;
		if (token->type == TK_WORD)
			cnt++;
		current = current->next;
	}
	return (cnt);
}

char	**get_args(t_list *token_list)
{
	char	**args;
	int		arg_count;
	int		i;
	t_list	*current;
	t_token	*token;

	if (!token_list)
		return (NULL);
	arg_count = count_args(token_list);
	args = (char **)malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		exit(EXIT_FAILURE);
	i = 0;
	current = token_list;
	token = (t_token *)current->content;
	while (current && token->type != TK_PIPE)
	{
		token = (t_token *)current->content;
		if (token->type == TK_WORD)
			args[i++] = token->value;
		current = current->next;
	}
	args[i] = NULL;
	return (args);
}

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
				break ;
		}
		i++;
	}
	return (s_tmp);
}
