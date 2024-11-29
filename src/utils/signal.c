/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:53:59 by yublee            #+#    #+#             */
/*   Updated: 2024/11/29 18:56:15 by yublee           ###   ########.fr       */
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