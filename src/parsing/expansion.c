/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:29:35 by yublee            #+#    #+#             */
/*   Updated: 2024/12/09 20:28:35 by yublee           ###   ########.fr       */
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

static char	*expand_var(t_env *env, size_t n_len, char *s, size_t i, int status)
{
	char	*new_str;
	char	*tmp;
	char	*exp_str;
	int		flag;

	new_str = ft_strdup(s);
	flag = 0;
	if (env)
		exp_str = env->var;
	else if (s[i + 1] == '?')
	{
		exp_str = ft_itoa(status);
		if (!exp_str)
			exit(EXIT_FAILURE);
		flag = 1;
	}
	else
		exp_str = NULL;
	tmp = new_str;
	new_str = expand_str(s, i, exp_str, n_len);
	free(tmp);
	free(s);
	if (flag)
		free(exp_str);
	return (new_str);
}

t_env	*search_name_in_env(t_env **env_lst, size_t name_len, char *str)
{
	t_env	*current;

	current = *env_lst;
	while (current)
	{
		if (name_len == ft_strlen(current->name)
			&& !ft_strncmp(str, current->name, name_len))
			break ;
		current = current->next;
	}
	return (current);
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
			name_len = 0;
			if (str[i] == '?')
				name_len = 1;
			else
			{
				while (str[i + name_len] && !isspace(str[i + name_len])
					&& str[i + name_len] != '\'' && str[i + name_len] != '\"')
					name_len++;
			}
			if (name_len)
			{
				env = search_name_in_env(env_lst, name_len, str + i);
				i--;
				str = expand_var(env, name_len, str, i, status);
				if (env)
					i += ft_strlen(env->var);
			}
		}
	}
	return (str);
}

//mask only single quote
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
		single_q_masked_str = mask_single_quoted_part(token->value);
		if (ft_strchr(single_q_masked_str, '$'))
			token->value = expand_dollar_sign(token->value, env_lst, status);
		free(single_q_masked_str);
		node = node->next;
	}
}
