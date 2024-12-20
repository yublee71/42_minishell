/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:19:22 by yublee            #+#    #+#             */
/*   Updated: 2024/12/11 18:41:59 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../../include/minishell.h"

int		ft_cd(char **args, t_info *info);
int		ft_echo(char **args, t_info *info);
int		ft_export(char **args, t_env **env_lst);
int		ft_pwd(void);
int		ft_unset(char **args, t_env **env_lst);
int		ft_env(t_info *info);
int		ft_exit(char **args, t_info *info);
t_env	*find_name_in_env(char *name, size_t name_len, t_env **env_lst);

#endif