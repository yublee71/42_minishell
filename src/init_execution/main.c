/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 23:32:48 by yublee            #+#    #+#             */
/*   Updated: 2024/08/09 04:18:32 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static t_info	get_info(t_list **cmd_list, t_ast *root, char **env)
{
	t_info	info;

	info.env = env;
	info.cmd_cnt = ft_lstsize(*cmd_list);
	info.cmd_list = cmd_list;
	info.root = root;
	return (info);
}

t_info	init_executor()
{
	

}
