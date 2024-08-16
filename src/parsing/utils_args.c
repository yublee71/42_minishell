/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 01:19:29 by yublee            #+#    #+#             */
/*   Updated: 2024/08/16 16:07:23 by yublee           ###   ########.fr       */
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
