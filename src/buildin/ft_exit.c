/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoi <tchoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:23:14 by tchoi             #+#    #+#             */
/*   Updated: 2024/08/24 16:02:15 by tchoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"


int		ft_validate_argu(char *str)
{
	int		i;

	i = 0;
	while(str[i] == '+' || str[i] == '-')
		i++;
	while(str[i])
	{
		if(ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int		ft_exit(int argc, char **argv, t_info *info)
{
	int		exit_status;

	exit_status = 0;
	if (argc == 1) //if no followed argu -> use the globol exit status set by the last execution 
		exit_with_message(NULL, info->exit, info);
	if (argc == 2) // if 1 argu
	{
		if(ft_validate_argu(argv[1])) //is number
		{
			exit_status = ft_atoi(argv[1]); 
			if (exit_status < 0) //is negative number -> error
				exit_with_message("Exit error: not support negative number", 1, info);
			else //is positive number -> % 255
				exit_with_message(NULL, (exit_status % 255), info);
		}
		else // if it is a text, print out error msg, set exit status as 2
			exit_with_message("Exit error: numberic number needed", 2, info);
	}
	if (argc > 2)// if more than 1 argu, print out error msg, set exit status as 1
		exit_with_message("Exit error: too many arguments", 1, info);
}
