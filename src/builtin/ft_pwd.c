/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:28:26 by tchoi             #+#    #+#             */
/*   Updated: 2024/12/09 01:43:35 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_pwd(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (!str)
	{
		write(2, "Error: pwd\n", ft_strlen("Error: pwd\n"));
		return (1);
	}
	printf("%s\n", str);
	free(str);
	return (0);
}
