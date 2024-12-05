/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:18:48 by yublee            #+#    #+#             */
/*   Updated: 2024/12/05 00:47:49 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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

static void	ft_initenv(char **env, t_env **env_arr)
{
	int		i;
	int		name_len;
	int		env_len;
	t_env	*new_env;
	t_env	**current;

	current = env_arr;
	i = 0;
	name_len = 0;
	env_len = 0;
	while (env[i])
	{
		new_env = malloc(sizeof(t_env));
		if (!new_env)
			return ; //error_handle
		name_len = ft_strchr(env[i], '='); // name= ; search for '=', return 4
		if (!name_len)
			exit(EXIT_FAILURE); //error handle
		env_len = ft_strlen(env[i]) - name_len;
		new_env->name = malloc(sizeof(char *) * name_len + 1);
		new_env->var = malloc(sizeof(char *) * env_len);
		if ((!new_env->name) || (!new_env->var))
			return ;
		new_env->name = ft_substr(env[i], 0, name_len);
		new_env->var = ft_substr(env[i], name_len + 1, env_len);
		new_env->next = NULL;
		ft_envadd_back(env_arr, new_env);
		i++;
	}
}

//TODO: modify
int	call_builtin(char **env) // combine to the set up function, should be ready when first start the shell
{
	int		env_count;
	t_env	**env_arr;

	env_count = array_size(env);
	env_arr = malloc(sizeof(t_env *) * env_count);
	ft_initenv(env, env_arr);
	//t_env *temp = *env_arr;
	//while (temp)
	//{
	//	printf("%s=%s\n", temp->name, temp->var);
	//	temp = temp->next;
	//}
	ft_unset("PWD", env_arr);
	//temp = *env_arr;
	//while (temp) 
	//{
	//	printf("%s=%s\n", temp->name, temp->var);
	//	temp = temp->next;
	//}
	free(env_arr); // Free the array itself
}
