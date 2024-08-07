/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:56:28 by yublee            #+#    #+#             */
/*   Updated: 2024/08/07 01:32:04 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strtrim_and_free(t_btree *root)
{
	char	*result;

	if (ft_strlen(root->item) > 0)
	{
		result = ft_strtrim(root->item, " ");
		free(root->item);
		root->item = result;
	}
}

static size_t	ft_wordcount(char *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*ft_copytil(char *s, char *s_sub, char c)
{
	size_t	len;
	size_t	i;
	char	*result;

	len = 0;
	i = 0;
	while (s_sub[len] != c && s_sub[len])
		len++;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	while (i < len)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	**ft_split_except_quoted_part(char *s, char c)
{
	char	*s_sub;
	size_t	i;
	size_t	j;
	char	**result;

	if (!s)
		return (NULL);
	s_sub = mask_quoted_part(s);
	result = (char **)malloc((ft_wordcount(s_sub, c) + 1) * sizeof(char *));
	if (!result)
		exit(EXIT_FAILURE);
	i = -1;
	j = 0;
	while (++i < ft_wordcount(s_sub, c))
	{
		while (s_sub[j] == c)
			j++;
		if (s_sub[j])
			result[i] = ft_copytil(&s[j], &s_sub[j], c);
		while (s_sub[j] != c && s_sub[j])
			j++;
	}
	result[i] = NULL;
	free(s_sub);
	return (result);
}

