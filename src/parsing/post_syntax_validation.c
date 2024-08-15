/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_syntax_validation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:21:09 by yublee            #+#    #+#             */
/*   Updated: 2024/08/09 04:24:57 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	post_syntax_validation(t_list *token_list)
{
	t_list	*current;
	t_list	*tmp;
	t_token	*token;

	current = token_list;
	while (current)
	{
		token = (t_token *)current->content;
		if (token->type == TK_INPUT || token->type == TK_HEREDOC
			|| token->type == TK_OUTPUT || token->type == TK_APPEND)
		{
			if (!current->next)
				return (-1);
			tmp = current->next;
			token = (t_token *)tmp->content;
			if (token->type != TK_WORD)
				return (-1);
			token->type = TK_FILE;
		}
		current = current->next;
	}
	return (0);
}
