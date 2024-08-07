/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:34:13 by yublee            #+#    #+#             */
/*   Updated: 2024/08/07 02:49:30 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*cmd;
	t_list	*token_list;

	(void)argc;
	(void)env;
	open("args.txt", O_TRUNC | O_CREAT, 0777); //only for test
	if (argv[1])
	{
		cmd = ft_strdup(argv[1]);
		if (!cmd)
			exit(EXIT_FAILURE);

		token_list = parser(cmd, env);

		// print list to check
		ft_lstiter(token_list, print_token);

		// pass cmd list to pipex
		// pipex(&token_list, env);

		//free only when testing
		ft_lstclear(&token_list, free_token);
		free(cmd);
	}
}
