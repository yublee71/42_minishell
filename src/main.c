/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:34:13 by yublee            #+#    #+#             */
/*   Updated: 2024/11/27 22:30:01 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_info	info;
	t_ast	*root;
	char	*cmd;

	(void)argc;
	(void)argv;
	//TODO: signal
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	while (1)
	{
		cmd = readline("minishell$ ");
		if (cmd)
		{
			if (ft_strlen(cmd))
			{
				root = parser(cmd, env);//TODO:env needs to be modified beforehand
				// ast_apply_infix(root, ast_print_node); //print tree
				//free only when testing without execution
				// free_array_until((void **)info.fds, info.cmd_cnt - 1);
				// ast_apply_suffix(root, ast_free_node);
				if (root)
				{
					info = init_executor(root, env);
					executor(root, &info);
				}
			}
		}
		else
		{
			printf("exit\n");
			break ;
		}
		add_history(cmd);
		free(cmd);
	}
	rl_clear_history();
}
