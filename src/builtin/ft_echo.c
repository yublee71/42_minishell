/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:30:58 by tchoi             #+#    #+#             */
/*   Updated: 2024/12/09 00:34:05 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

//check if there is -n, and return the index after the -n
//or return 0 if there is not = can print out the str starting from index
static int	check_newline_option(char *arg)
{
	static char	*option = "-n";

	if (arg && ft_strlen(arg) == 2 && !ft_strncmp(arg, option, 2))
		return (1);
	return (0);
}

//check if it has option -n : do not output the trailing newline
//if yes, print new line \n
//if no, just print the following str
// echo -n abcd -> abcd\n
// echo xyz -> xyz
int	ft_echo(char **args)
{
	int		i;
	int		newline_opt;

	i = 1;
	newline_opt = check_newline_option(args[i]);
	if (newline_opt)
		i++;
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
		if (args[i])
			printf(" ");
	}
	if (!newline_opt)
		printf("\n");
	return (0);
}
