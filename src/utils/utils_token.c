/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 02:31:29 by yublee            #+#    #+#             */
/*   Updated: 2024/08/07 02:32:24 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
