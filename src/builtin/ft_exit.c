/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:23:14 by tchoi             #+#    #+#             */
/*   Updated: 2024/12/09 19:33:41y yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_validate_argu(char *str)
{
	int		i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args, t_info *info)
{
	int		exit_status;
	int		arg_size;
	char	*err_msg;

	printf("exit\n");
	arg_size = array_size((void **)args);
	err_msg = NULL;
	exit_status = 0;
	if (arg_size == 1 || arg_size == 2)
	{
		if (args[1] && is_validate_argu(args[1]))
		{
			exit_status = ft_atoi(args[1]) % 256;
			if (exit_status < 0)
				exit_status += 256;
		}
		else if (args[1])
		{
			err_msg = "exit: numberic argument required\n";
			exit_status = 2;
		}
		exit_with_message(err_msg, exit_status, info);
	}
	write(2, "exit: too many arguments\n", 25);
	return (1);
}