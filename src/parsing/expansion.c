/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:29:35 by yublee            #+#    #+#             */
/*   Updated: 2024/12/08 03:06:06 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*expand_str(char *new_str, char *var, size_t name_len)
{
	size_t	dollar_len;
	size_t	head_len;
	size_t	tail_len;
	size_t	var_len;
	char	*str;

	dollar_len = ft_strlen(ft_strchr(new_str, '$'));
	head_len = ft_strlen(new_str) - dollar_len;
	tail_len = dollar_len - name_len - 1;
	var_len = 0;
	if (var)
		var_len = ft_strlen(var);
	str = (char *)ft_malloc(head_len + var_len + tail_len + 1);
	if (!str)
		exit(EXIT_FAILURE);
	ft_strncat(str, new_str, head_len);
	if (var)
		ft_strncat(str, var, ft_strlen(var));
	ft_strncat(str, new_str + head_len + 1 + name_len, tail_len);
	return (str);
}

static char	*expand_dollar_sign(char *value, t_env **env_lst)
{
	size_t	name_len;
	char	*new_str;
	char	*dollar_str;
	char	*tmp;
	t_env	*current;

	current = *env_lst;
	new_str = value;
	while (ft_strchr(new_str, '$'))
	{
		name_len = 0;
		dollar_str = ft_strchr(new_str, '$');
		while (dollar_str[name_len] &&
			!isspace(dollar_str[name_len]) && dollar_str[name_len] != '\'' && dollar_str[name_len] != '\"')
			name_len++;
		name_len--;
		if (!name_len)
			return (new_str);
		while (current)
		{
			if (name_len == ft_strlen(current->name) &&
				!ft_strncmp(dollar_str + 1, current->name, name_len))
			{
				tmp = new_str;
				new_str = expand_str(new_str, current->var, name_len);
				free(tmp);
				break ;
			}
			current = current->next;
		}
		if (!current)
			new_str = expand_str(new_str, NULL, name_len);
	}
	return (new_str);
}

//mask only single quote
void	expand_env_var(t_list *token_list, t_env **env_lst)
{
	t_list	*node;
	t_token	*token;
	char	*single_q_masked_str;

	if (!token_list)
		return ;
	node = token_list;
	while (node)
	{
		token = (t_token *)node->content;
		single_q_masked_str = mask_single_quoted_part(token->value);
		if (ft_strchr(single_q_masked_str, '$'))
			token->value = expand_dollar_sign(token->value, env_lst);
		free(single_q_masked_str);
		node = node->next;
	}
}