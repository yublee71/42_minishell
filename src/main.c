/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:34:13 by yublee            #+#    #+#             */
/*   Updated: 2024/08/09 04:42:23 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*cmd;
	// t_list	*token_list;
	// t_info	*info;
	t_ast	*root;

	(void)argc;
	(void)env;
	open("args.txt", O_TRUNC | O_CREAT, 0777); //only for test
	if (argv[1])
	{
		cmd = ft_strdup(argv[1]);
		if (!cmd)
			exit(EXIT_FAILURE);

		// token_list = parser(cmd, env);
		root = parser(cmd, env);

		tree_apply_infix(root, tree_print_node);
		// print list to check
		// ft_lstiter(token_list, print_token);

		// init_executor()
		// pass cmd list to pipex
		// pipex(&token_list, env);

		//free only when testing
		tree_apply_suffix(root, tree_free_node);
		// ft_lstclear(token_list, free_token);
		free(cmd);
	}
}

//free: cmd, root