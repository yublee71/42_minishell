/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:28:26 by tchoi             #+#    #+#             */
/*   Updated: 2024/12/03 19:26:47 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_pwd(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (!str)
	{
		printf("Error: pwd\n");
		exit(1);
	}
	printf("%s\n", str);
	return (0);
}
