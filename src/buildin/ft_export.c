/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoi <tchoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:05:31 by tchoi             #+#    #+#             */
/*   Updated: 2024/08/24 15:45:44 by tchoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"


static void ft_print_env(char *envstr)
{
	int i;
	int not_quoted; // if there are more than 1 '=' sign in the env, only add " after the first '=' sign

	i = 0;
	not_quoted = 1;
	ft_printf("declare -x ");
	while (envstr[i])
	{
		if ((envstr[i] == '=') && not_quoted)
		{
			printf("=\"");
			not_quoted = 0;
		}
		else
			printf("%c", envstr[i]);
		i++;
	}
	printf("\"\n");
}

static int count_env(t_env **env)
{
	int i;

	i = 0;
	while(*env)
    {
        i++;
        *env = (*env)->next;
    }
	return (i);
}

static int find_first_unsort_env(int *indexarr, char **env)
{
	int i = 0;
	while(indexarr[i] != -42)
	{
		if (indexarr[i] != -1)
			return(i);
		i++;
	}
}

static char **ft_sort_env(t_env **env, int *indexarr, char **sortedarr, int env_len)
{
	int i;
	int j;
	char *next_env; //temp to store the unsorted env
	int next_index; //indicate the index from the char **env

	i = -1;
	while(++i < env_len)
	{
		next_index = find_first_unsort_env(indexarr, env);
		next_env = env[next_index]; // assign the first un-sorted env
		j = -1;
		while (++j < env_len)
		{
			if ((indexarr[j] != -1) && ((ft_strncmp(next_env, env[indexarr[j]], ft_strlen(next_env))) > 0)) //loop thru the whole env arr, compare each to the first un-sorted env
			{
				next_env = env[indexarr[j]];
				next_index = j;
			}
		}
		sortedarr[i] = next_env;
		indexarr[next_index] = -1;
	}
	sortedarr[j] = NULL;
	return(sortedarr);
}

int ft_export(t_info *info)
{
	int count;
	int *indexarr; // keep track on the sorted env, if already allocated to the right place, will update to -1 e.g. [0,1,2,3,4,5,-1,7,-1]
	char **sortedenv;
	int i;

	count = count_env(info->env);
	indexarr = malloc(sizeof(int) * (count + 1));
	sortedenv = malloc(sizeof(char *) * (count + 1));
	if(!indexarr || !sortedenv)
		exit_with_message("malloc", EXIT_FAILURE, info);
	i = -1;
	while(++i < count) // init the value for index arr [0,1,2, ... ,-42]
		indexarr[i] = i;
	indexarr[i] = -42;
	sortedenv = ft_sort_env(info->env, indexarr, sortedenv, count);
	i = -1;
	while (sortedenv[++i])
		ft_print_env(sortedenv[i]);
	free(indexarr);
	free(sortedenv);
	return(0);
}