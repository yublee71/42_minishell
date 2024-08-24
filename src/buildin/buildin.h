/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchoi <tchoi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:06:34 by tchoi             #+#    #+#             */
/*   Updated: 2024/08/24 17:14:51 by tchoi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDIN_H
# define BUILDIN_H

# include "../../include/minishell.h"

//ft_cd
int		ft_cd(char *path_to_go, t_info *info);

//ft_echo
int		ft_echo(char *str);

//ft_env
int		ft_env(t_info *info);

//ft_exit
int		ft_exit(int argc, char **argv, t_info *info);

//ft_export
int		ft_export(t_info *info);

//ft_pwd
int		ft_pwd(t_info *info);

//ft_unset
int		ft_unset(char *name, t_info *info);

#endif