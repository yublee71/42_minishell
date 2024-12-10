/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:29:35 by yublee            #+#    #+#             */
/*   Updated: 2024/12/09 21:19:39 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*expand_str(char *new_str, size_t i, char *var, size_t name_len)
{
	size_t	head_len;
	size_t	tail_len;
	size_t	var_len;
	char	*str;

	head_len = i;
	tail_len = ft_strlen(new_str) - head_len - 1 - name_len;
	var_len = 0;
	if (var)
		var_len = ft_strlen(var);
	str = (char *)ft_calloc(head_len + var_len + tail_len + 1, 1);
	if (!str)
		exit(EXIT_FAILURE);
	str = ft_strncat(str, new_str, head_len);
	if (var)
		str = ft_strncat(str, var, ft_strlen(var));
	str = ft_strncat(str, new_str + head_len + 1 + name_len, tail_len);
	return (str);
}

static char	*expand_var(t_env *env, char *s, size_t i, int status)
{
	char	*new_str;
	char	*exp_str;
	int		flag;
	size_t	name_len;

	flag = 0;
	name_len = count_name_len(s, i + 1);
	if (env)
		exp_str = env->var;
	else if (s[i + 1] == '?')
	{
		exp_str = ft_itoa(status);
		flag = 1;
		name_len = 1;
	}
	else
		exp_str = NULL;
	new_str = expand_str(s, i, exp_str, name_len);
	free(s);
	if (flag)
		free(exp_str);
	return (new_str);
}

static char	*expand_dollar_sign(char *str, t_env **env_lst, int status)
{
	size_t	name_len;
	size_t	i;
	t_env	*env;

	i = 0;
	while (str[i])
	{
		if (str[i++] == '$')
		{
			if (str[i] == '?')
				name_len = 1;
			else
				name_len = count_name_len(str, i);
			if (name_len)
			{
				env = search_name_in_env(env_lst, name_len, str + i);
				i--;
				str = expand_var(env, str, i, status);
				if (env)
					i += ft_strlen(env->var);
			}
		}
	}
	return (str);
}

//expands with/without double quotes, doesn't expand with single quotes
void	expand_env_var(t_list *token_list, t_env **env_lst, int status)
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
		if (token->type == TK_HEREDOC)
		{
			node = node->next->next;
			continue;
		}
		single_q_masked_str = mask_single_quoted_part(token->value);
		if (ft_strchr(single_q_masked_str, '$'))
			token->value = expand_dollar_sign(token->value, env_lst, status);
		free(single_q_masked_str);
		node = node->next;
	}
}
