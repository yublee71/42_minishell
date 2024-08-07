/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 22:18:56 by yublee            #+#    #+#             */
/*   Updated: 2024/08/07 01:29:22 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*parser(char *cmd, char **env)
{
	t_list	*token_list;

	if (pre_syntax_validation(cmd) < 0)
	{
		free(cmd);
		write(2, "Syntax error\n", ft_strlen("Syntax error\n"));
		exit(EXIT_FAILURE);
	}
	token_list = tokenizer(cmd);
	if (post_syntax_validation(token_list) < 0)
	{
		free(cmd);
		ft_lstclear(&token_list, free);
		write(2, "Syntax error\n", ft_strlen("Syntax error\n"));
		exit(EXIT_FAILURE);
	}
	expand_env_var(token_list, env);
	ft_lstiter(token_list, remove_quotes);
	return (token_list);
}

//gcc -L../../lib/ft -Wall -Wextra -Werror *.c -lft

int	main(int argc, char **argv, char **env)
{
	char	*cmd;
	t_list	*token_list;

	(void)argc;
	(void)env;
	if (argv[1])
	{
		cmd = ft_strdup(argv[1]);
		if (!cmd)
			exit(EXIT_FAILURE);

		token_list = parser(cmd, env);

		ft_lstiter(token_list, print_token);

		free(cmd);
		ft_lstclear(&token_list, free_token);
	}
}

