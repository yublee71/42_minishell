/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoi <tchoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:51:48 by tchoi             #+#    #+#             */
/*   Updated: 2024/08/18 12:07:31 by tchoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

//check if there is -n, and return the index after the -n
//or return 0 if there is not = can print out the str starting from index
int		check_newline_option(char *str)
{
	int i = 0;

	if (str[0] == '-' && str[1] == 'n')
	{
		i++;
		while (str[i] == 'n')
			i++;
		while (ft_isspace(str[i]))
			i++;
		return(i);
	}
	return (i);
}

//check if it has option -n : do not output the trailing newline
//if yes, print new line \n
//if no, just print the following str
// echo -n abcd -> abcd\n
// echo xyz -> xyz
int		ft_echo(char *str)
{
    int i;
    int newline;

    newline = 1; //default has to output trailing newline
    i = check_newline_option(str);
    if (i > 1)
        newline = 0;
    while(str[i])
    {
        ft_putchar_fd(str[i], 1);   
        i++;
    }
    if (newline)
        ft_putchar_fd('\n', 1);
    return (0);
}