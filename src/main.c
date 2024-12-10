/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:34:13 by yublee            #+#    #+#             */
/*   Updated: 2024/12/09 20:21:00 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_sigint_received = 0;

static int	event(void) { 
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_info	info;
	t_ast	*root;
	char	*cmd;
	t_env	**env_lst;
	int		*status_store;
	int		status;

	(void)argc;
	(void)argv;
	if (isatty(STDIN_FILENO))
		rl_event_hook = event;
	else
		rl_event_hook = NULL;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	env_lst = get_env_lst(env);
	status = 0;
	status_store = &status;
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
				root = parser(cmd, env_lst, *status_store);
				// ast_apply_infix(root, ast_print_node); //print tree
				if (root)
				{
					info = init_executor(root, env, env_lst, status_store);
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
	free_env(env_lst);
	rl_clear_history();
	return (*(info.status));
}
