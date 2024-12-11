/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:34:13 by yublee            #+#    #+#             */
/*   Updated: 2024/12/11 00:47:06 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_sigint_received = 0;

static void	parse_and_execute(char *cmd, t_env **env_lst, int *status_stored)
{
	t_ast	*root;
	t_info	info;

	root = parser(cmd, env_lst, *status_stored);
	// ast_apply_infix(root, ast_print_node); //print tree
	if (root)
	{
		info = init_executor(root, environ, env_lst, status_stored);
		executor(root, &info);
	}
}

static void	minishell(t_env **env_lst, int *status_stored)
{
	char	*cmd;

	while (1)
	{
		if (g_sigint_received)
		{
			g_sigint_received = 0;
			continue ;
		}
		cmd = readline("minishell$ ");
		if (cmd && ft_strlen(cmd))
			parse_and_execute(cmd, env_lst, status_stored);
		else if (!cmd)
		{
			printf("exit\n");
			break ;
		}
		add_history(cmd);
		free(cmd);
	}
}

int	main(void)
{
	t_env	**env_lst;
	int		*status_stored;
	int		status;

	setup_signal();
	env_lst = get_env_lst(environ);
	status = 0;
	status_stored = &status;
	minishell(env_lst, status_stored);
	free_env(env_lst);
	rl_clear_history();
	return (*status_stored);
}
