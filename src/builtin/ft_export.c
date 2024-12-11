/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:47:01 by tchoi             #+#    #+#             */
/*   Updated: 2024/12/11 18:41:05 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_env	*find_name_in_env(char *name, size_t name_len, t_env **env_lst)
{
	t_env	*current;

	current = *env_lst;
	while (current)
	{
		if (name_len == ft_strlen(current->name)
			&& !ft_strncmp(name, current->name, name_len))
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	invalid_name(char *name)
{
	size_t	i;

	i = 0;
	if (!ft_strlen(name) || (name[0] >= '0' && name[0] <= '9'))
		return (1);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static void	modify_env(char *name, char *var, size_t name_len, t_env **env_lst)
{
	t_env	*env;
	char	*tmp;

	env = find_name_in_env(name, name_len, env_lst);
	var++;
	if (env)
	{
		tmp = env->var;
		env->var = ft_strdup(var);
		free(tmp);
	}
	else
	{
		env = (t_env *)malloc(sizeof(t_env));
		if (!env)
			exit(EXIT_FAILURE);
		env->name = ft_strdup(name);
		env->var = ft_strdup(var);
		env->next = NULL;
		ft_envadd_back(env_lst, env);
	}
}

static int	export_arg(char *arg, t_env **env_lst)
{
	char	*name;
	char	*var;
	size_t	name_len;
	char	*err_msg;

	var = ft_strchr(arg, '=');
	if (!var)
		name_len = ft_strlen(arg);
	else
		name_len = ft_strlen(arg) - ft_strlen(var);
	name = ft_strndup(arg, name_len);
	if (invalid_name(name))
	{
		write(2, name, ft_strlen(name));
		err_msg = ": not a valid identifier\n";
		write(2, err_msg, ft_strlen(err_msg));
		free(name);
		return (1);
	}
	if (var)
		modify_env(name, var, name_len, env_lst);
	free(name);
	return (0);
}

int	ft_export(char **args, t_env **env_lst)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (args[++i])
	{
		if (export_arg(args[i], env_lst))
			status = 1;
	}
	return (status);
}
