/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 22:18:56 by yublee            #+#    #+#             */
/*   Updated: 2024/12/09 03:15:30 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_ast	*parser(char *cmd, t_env **env_lst, int status)
{
	t_list	*token_list;
	t_ast	*root;

	if (pre_syntax_validation(cmd) < 0)
	{
		write(2, "Syntax error\n", ft_strlen("Syntax error\n"));
		return (NULL);
	}
	token_list = tokenizer(cmd);
	if (post_syntax_validation(token_list) < 0) //TODO
	{
		ft_lstclear(&token_list, free);
		write(2, "Syntax error\n", ft_strlen("Syntax error\n"));
		return (NULL);
	}
	expand_env_var(token_list, env_lst, status);
	ft_lstiter(token_list, remove_quotes);
	root = build_tree(token_list);
	ft_lstclear(&token_list, free);
	return (root);
}
