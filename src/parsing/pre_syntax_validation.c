/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_syntax_validation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:57:05 by yublee            #+#    #+#             */
/*   Updated: 2024/12/11 17:07:01 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	first_char(char *str)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(str);
	i = 0;
	while (i < len && str[i] == ' ')
		i++;
	if (i == len)
		return (0);
	return (str[i]);
}

static char	last_char(char *str)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(str);
	i = len - 1;
	while (i > 0 && str[i] == ' ')
	{
		i--;
		if (!i)
			break ;
	}
	return (str[i]);
}

static int	balance_check(char *str)
{
	size_t	len;
	size_t	i;
	char	quote;

	if (!str)
		return (-1);
	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			while (str[++i] != quote && i < len)
				;
			if (i == len)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	pre_syntax_validation(char *cmd)
{
	if (first_char(cmd) == '|' || balance_check(cmd) < 0
		|| last_char(cmd) == '|')
		return (-1);
	return (0);
}
