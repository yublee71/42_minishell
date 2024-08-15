/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 22:18:56 by yublee            #+#    #+#             */
/*   Updated: 2024/08/15 15:26:50 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_ast	*parser(char *cmd, char **env)
{
	t_list	*token_list;
	t_ast	*root;

	if (pre_syntax_validation(cmd) < 0)
	{
		write(2, "Syntax error\n", ft_strlen("Syntax error\n"));
		exit(EXIT_FAILURE);
	}
	token_list = tokenizer(cmd);
	if (post_syntax_validation(token_list) < 0) //TODO
	{
		ft_lstclear(&token_list, free);
		write(2, "Syntax error\n", ft_strlen("Syntax error\n"));
		exit(EXIT_FAILURE);
	}
	expand_env_var(token_list, env); //TODO
	ft_lstiter(token_list, remove_quotes); //TODO
	root = build_tree(token_list);
	ft_lstclear(&token_list, free);
	return (root);
}
//gcc -L../../lib/ft -Wall -Wextra -Werror *.c -lft
