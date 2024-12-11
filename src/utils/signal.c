/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:53:59 by yublee            #+#    #+#             */
/*   Updated: 2024/12/11 00:47:54 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	g_sigint_received = 1;
	rl_replace_line("", 0);
	rl_on_new_line();
	printf("\n");
	rl_done = 1;
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_sigint_received = 1;
	rl_done = 1;
}

static int	event(void)
{
	return (0);
}

void	setup_signal(void)
{
	if (isatty(STDIN_FILENO))
		rl_event_hook = event;
	else
		rl_event_hook = NULL;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
