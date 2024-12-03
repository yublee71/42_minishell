/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tikochoi <tikochoi@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-27 21:55:17 by tikochoi          #+#    #+#             */
/*   Updated: 2024-11-27 21:55:17 by tikochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../lib/ft/include/libft.h"

static int ft_count_env(char **env)
{
    int i = 0;

    while(env[i])
        i++;
    return(i);
}

static t_env	*ft_lstlast(t_env *lst)
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
	last = ft_lstlast(*lst);
	last->next = new;
}

static void    ft_initenv(char **env, t_env **env_arr)
{
    int i = 0;
    int name_len = 0;
    int env_len = 0;
	t_env *new_env;
    t_env **current = env_arr;

    while(env[i])
    {
        new_env = malloc(sizeof(t_env));
		if(!new_env)
			return; //error_handle
        name_len = ft_strchr(env[i], '='); // name= ; search for '=', return 4
        if (!name_len)
            exit(EXIT_FAILURE); //error handle
		env_len = ft_strlen(env[i]) - name_len;
        new_env->name = malloc(sizeof(char *) * name_len + 1);
		new_env->var = malloc(sizeof(char *) * env_len);
		if((!new_env->name) || (!new_env->var))
			return ;
		new_env->name = ft_substr(env[i], 0, name_len); 
		new_env->var = ft_substr(env[i], name_len + 1, env_len);
		new_env->next = NULL;
		ft_envadd_back(env_arr, new_env);
		i++;
    }
}

int ft_unset(char *name, t_env **env_arr) 
{
    int i = ft_strlen(name);
    t_env *temp;
    t_env **current = env_arr;

    while (*current) {
        if (!ft_strncmp(name, (*current)->name, i)) // matched
		{
            temp = *current;
            *current = (*current)->next;
            free(temp->name);
            free(temp->var);
            free(temp);
            return (1);
        }
        current = &(*current)->next;
    }
    return (0);
}

int main(int argc, char **argv, char **env) // combine to the set up function, should be ready when first start the shell
{
    int env_count = ft_count_env(env);
    t_env **env_arr = malloc(sizeof(t_env *) * env_count);
    ft_initenv(env, env_arr);
    //t_env *temp = *env_arr;
    //while (temp) 
	//{
    //    printf("%s=%s\n", temp->name, temp->var);
    //    temp = temp->next;
    //}
    ft_unset("PWD", env_arr);
    //temp = *env_arr;
    //while (temp) 
	//{
    //    printf("%s=%s\n", temp->name, temp->var);
    //    temp = temp->next;
    //}
    free(env_arr); // Free the array itself
}