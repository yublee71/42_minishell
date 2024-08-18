/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoi <tchoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:32:50 by tchoi             #+#    #+#             */
/*   Updated: 2024/08/18 15:07:29 by tchoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

int ft_count_env(char **env)
{
	int i = 0;

	while(env[i])
		i++;
	return(i);
}

void    ft_initenv(char **env, t_env **env_arr)
{
	int i = 0;
	int name_len = 0;
	int env_len = 0;
	t_env *new_env;

	while(env[i])
	{
		new_env = malloc(sizeof(t_env));
		if(!new_env)
			return; //error_handle
		name_len = ft_strchr_index(env[i], '='); // name= ; search for '=', return 4
		env_len = ft_strlen(env[i]) - name_len;
		new_env->name = malloc(sizeof(char *) * name_len + 1);
		new_env->var = malloc(sizeof(char *) * env_len);
		if((!new_env->name) || (!new_env->var))
			return ; //erro handle
		new_env->name = ft_strcpy_from(env[i], 0, name_len); // copy str from 0 to right before the '='
		new_env->var = ft_strcpy_from(env[i], name_len + 1, env_len); //copy str from after the '=' to end of the str
		new_env->next = NULL;
		ft_envadd_back(env_arr, new_env);
		i++;
    }
}

int     ft_strchr_index(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return (i);
		else
			i++;
	}
	return (-1); //normally wont return -1, as every env has the '=', edge case???
}

char	*ft_strcpy_from(const char *s, int from_index, int cpy_len)
{
	int		i;
	char	*arr;

	i = 0;
	arr = malloc((cpy_len + 1) * sizeof(char));
	if (arr == NULL)
		return (NULL);
	while (i < cpy_len)
	{
		arr[i] = s[from_index];
		i++;
		from_index++;
	}
	arr[i] = 0;
	return (arr);
}

t_env	*ft_envlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_envlast(*lst);
	last->next = new;
}
