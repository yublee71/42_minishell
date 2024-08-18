/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoi <tchoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:42:10 by tchoi             #+#    #+#             */
/*   Updated: 2024/08/18 12:07:36 by tchoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

int		ft_pwd(t_info *info)
{
	char *str;
	str = getcwd(NULL, 0);
	if(!str)
		exit_with_message("pwd", EXIT_FAILURE, info);
	ft_printf("%s\n", str);
	return(0);
}