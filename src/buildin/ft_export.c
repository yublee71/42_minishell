/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoi <tchoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:05:31 by tchoi             #+#    #+#             */
/*   Updated: 2024/08/18 14:37:12 by tchoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"


void ft_print_env(char *envstr)
{
	int i;
	int quoted;

	i = 0;
	quoted = 1;
	ft_printf("declare -x ");
	while (envstr[i])
	{
		if ((envstr[i] == '=') && quoted)
		{
			printf("=\"");
			quoted = 0;
		}
		else
			printf("%c", envstr[i]);
		i++;
	}
	printf("\"\n");
}

int count_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int find_first_unsort_env(int *indexarr, char **env)
{
	int i = 0;
	while(indexarr[i] != -42)
	{
		if (indexarr[i] != -1)
			return(i);
		i++;
	}
}

char **ft_sort_env(char **env, int *indexarr, char **sortedarr, int env_len)
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

int ft_export(char **env, t_info *info)
{
	int count;
	int *indexarr; // keep track on the sorted env, if already allocated to the right place, will update to -1 e.g. [0,1,2,3,4,5,-1,7,-1]
	char **sortedenv;
	int i;

	count = count_env(env);
	indexarr = malloc(sizeof(int) * (count + 1));
	sortedenv = malloc(sizeof(char *) * (count + 1));
	if(!indexarr || !sortedenv)
		exit_with_message("malloc", EXIT_FAILURE, info);
	i = -1;
	while(++i < count) // init the value for index arr [0,1,2, ... ,-42]
		indexarr[i] = i;
	indexarr[i] = -42;
	sortedenv = ft_sort_env(env, indexarr, sortedenv, count);
	i = -1;
	while (sortedenv[++i])
		ft_print_env(sortedenv[i]);
	free(indexarr);
	free(sortedenv);
	return(0);
}