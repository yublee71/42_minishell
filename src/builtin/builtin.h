/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:19:22 by yublee            #+#    #+#             */
/*   Updated: 2024/12/03 19:20:07 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../../include/minishell.h"

int		ft_cd(int argc, char **argv, t_env **env_arr);
int		ft_echo(char *str);
int		ft_env(t_env **env_arr, t_info *info);
int		ft_export(char **env);
int		ft_pwd(void);
int		ft_unset(char *name, t_env **env_arr);
int		ft_exit(int argc, char **argv, t_info *info);


#endif