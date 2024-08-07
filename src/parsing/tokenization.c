/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:26:10 by yublee            #+#    #+#             */
/*   Updated: 2024/08/07 02:00:28 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	add_token(char *value, t_token_type type, t_list **list)
{
	t_list	*new;
	t_token	*token;

	if (!value)
		exit(EXIT_FAILURE);
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		exit(EXIT_FAILURE);
	token->value = value;
	token->type = type;
	new = ft_lstnew((void *)token);
	if (!new)
		exit(EXIT_FAILURE);
	ft_lstadd_back(list, new);
}

static size_t	handle_operator(t_list **token_list, char *cmd)
{
	size_t	cnt;

	cnt = 1;
	if (*cmd == '<')
	{
		if (*(++cmd) == '<' && cnt++)
			add_token(ft_strdup("<<"), TK_HEREDOC, token_list);
		else
			add_token(ft_strdup("<"), TK_INPUT, token_list);
	}
	else if (*cmd == '>')
	{
		if (*(++cmd) == '>' && cnt++)
			add_token(ft_strdup(">>"), TK_APPEND, token_list);
		else
			add_token(ft_strdup(">"), TK_OUTPUT, token_list);
	}
	else
		add_token(ft_strdup("|"), TK_PIPE, token_list);
	return (cnt);
}

static size_t	handle_word(t_list **token_list, char *masked_cmd, char *cmd)
{
	char	*value;
	size_t	i;

	i = 0;
	while (masked_cmd[i] && !ft_isspace(masked_cmd[i])
		&& !ft_isoperater(masked_cmd[i]))
		i++;
	value = ft_strndup(cmd, i);
	if (masked_cmd[0] == '\'')
		add_token(value, TK_SQUOTE, token_list);
	else if (masked_cmd[0] == '"')
		add_token(value, TK_DQUOTE, token_list);
	else
		add_token(value, TK_WORD, token_list);
	return (i);
}

static t_list	*create_token_list(char *cmd, char *masked_cmd)
{
	size_t	i;
	size_t	cnt;
	t_list	*token_list;

	i = 0;
	token_list = NULL;
	while (masked_cmd[i])
	{
		while (ft_isspace(masked_cmd[i]))
			i++;
		if (masked_cmd[i])
		{
			if (ft_isoperater(masked_cmd[i]))
				cnt = handle_operator(&token_list, &cmd[i]);
			else
				cnt = handle_word(&token_list, &masked_cmd[i], &cmd[i]);
			i += cnt;
		}
	}
	return (token_list);
}

t_list	*tokenizer(char *cmd)
{
	char	*masked_cmd;
	t_list	*token_list;

	masked_cmd = mask_quoted_part(cmd);
	token_list = create_token_list(cmd, masked_cmd);
	free(masked_cmd);
	return (token_list);
}
