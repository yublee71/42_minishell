/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 00:51:02 by yublee            #+#    #+#             */
/*   Updated: 2024/12/05 01:01:49by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//TODO: add exit
void	free_env(t_env **env)
{
	t_env	*current;
	t_env	*next;

	current = *env;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->var);
		free(current);
		current = next;
	}
	free(env);
}

int	is_builtin(char *cmd)
{
	const char	*builtins[5] = {"cd", "echo", "export", "pwd", "unset"};
	int		i;

	i = 0;
	while (i < 5)
	{
		if (ft_strlen(cmd) == ft_strlen(builtins[i])
			&& !ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i])))
			return (i);
		i++;
	}
	return (-1);
}

static t_env	*ft_envlstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_envlstlast(*lst);
	last->next = new;
}

static void	ft_initenv(t_env **lst, char **env)
{
	int		i;
	int		name_len;
	int		env_len;
	t_env	*new_env;
	char	*var;

	i = 0;
	name_len = 0;
	env_len = 0;
	while (env[i])
	{
		new_env = (t_env *)malloc(sizeof(t_env));
		if (!new_env)
			exit(EXIT_FAILURE);
		var = ft_strchr(env[i], '='); // name= ; search for '=', return 4
		if (!var)
			exit(EXIT_FAILURE); //error handle
		name_len = ft_strlen(env[i]) - ft_strlen(var);
		env_len = ft_strlen(env[i]) - name_len;
		new_env->name = (char *)malloc(name_len + 1);
		new_env->var = (char *)malloc(env_len);
		if ((!new_env->name) || (!new_env->var))
			return ;
		new_env->name = ft_substr(env[i], 0, name_len);
		new_env->var = ft_substr(env[i], name_len + 1, env_len);
		new_env->next = NULL;
		ft_envadd_back(lst, new_env);
		i++;
	}
}

t_env	**get_env_lst(char **env)
{
	t_env	**lst;

	lst = (t_env **)malloc(sizeof(t_env *));
	*lst = NULL;
	ft_initenv(lst, env);
	return (lst);
}
