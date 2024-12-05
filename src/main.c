/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:34:13 by yublee            #+#    #+#             */
/*   Updated: 2024/12/05 02:02:53 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_sigint_received = 0;

int	event(void) { 
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_info	info;
	t_ast	*root;
	char	*cmd;

	(void)argc;
	(void)argv;
	rl_event_hook = event;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		if (g_sigint_received)
		{
			g_sigint_received = 0;
			continue;
		}
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
