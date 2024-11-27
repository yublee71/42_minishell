/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_ft_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoi <tchoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:47:01 by tchoi             #+#    #+#             */
/*   Updated: 2024/08/11 17:30:45 by tchoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../lib/ft/include/libft.h"


static void initindex(int **indexarr, int count)
{
    int i = 0;

    while(i < count)
    {
        *indexarr[i] = i;
        i++;
    }
    *indexarr[i] = -42;
}

static  int count_env(char **env)
{
    int i;

    i = 0;
    while (env[i])
        i++;
    return (i);
}

static  int find_first_nonuse(int *indexarr, char **env)
{
    int i = 0;
    while(indexarr[i] != -42)
    {
        if (indexarr[i] != -1)
        {
            indexarr[i] == -1;
            return(i);
        }
        i++;
    }
}

static char **ft_sort_env(char **env, int *indexarr, char **sortedarr, int env_len)
{
    int i, j = 0;
    char *first_env;
    int first_index;

    while(i < env_len)
    {
        first_index = find_first_notuse(indexarr, env);
        first_env = env[first_index];
        j = 0;
        while (j < env_len)
        {
            if(indexarr[j] != -1)
            {
                if ((ft_strncmp(first_env, env[indexarr[j]], ft_strlen(first_env))) > 0)
                {
                    first_env = env[indexarr[j]];
                    first_index = j;
                }
            }
            j++;
        }
        sortedarr[i] = first_env;
        indexarr[first_index] = -1;
        i++;
    }
    sortedarr[j] = NULL;
    return(sortedarr);
}

int ft_export(char **env)
{
    int count;
    int *indexarr; // keep track on the sorted env, if already allocated to the right place, will update to -1 e.g. [0,1,2,3,4,5,-1,7,-1]
    char **sortedarr;

    count = count_env(env);
    indexarr = malloc(sizeof(int) * (count + 1));
    sortedarr = malloc(sizeof(char *) * (count + 1));
    if(!indexarr || !sortedarr)
        exit(EXIT_FAILURE);
    initindex(&indexarr, count);
    sortedarr = ft_sort_env(env, indexarr, sortedarr, count);
}

