/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:34:13 by yublee            #+#    #+#             */
/*   Updated: 2024/08/15 14:17:20 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_info	info;
	t_ast	*root;

	(void)argc;
	if (argv[1])
	{
		root = parser(argv[1], env);//TODO:env needs to be modified beforehand
		// ast_apply_infix(root, ast_print_node);

		info = init_executor(root, env);

		executor(root, &info);

		//free only when testing
		// free_array_until((void **)info.fds, info.cmd_cnt - 1);
		// ast_apply_suffix(root, ast_free_node);
	}
}
