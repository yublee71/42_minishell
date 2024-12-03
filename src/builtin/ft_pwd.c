/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_ft_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoi <tchoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:28:26 by tchoi             #+#    #+#             */
/*   Updated: 2024/08/11 18:15:29 by tchoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../lib/ft/include/libft.h"

int ft_pwd(void)
{
    char *str;
    str = getcwd(NULL, 0);
    if(!str)
    {
        printf("Error: pwd\n");
		exit(1);
    }
    printf("%s\n", str);
    return(0);
}