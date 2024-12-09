/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 21:27:36 by yublee            #+#    #+#             */
/*   Updated: 2024/12/09 00:45:33 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../../include/minishell.h"

//main
int		pre_syntax_validation(char *cmd);
t_list	*tokenizer(char *cmd);
int		post_syntax_validation(t_list *token_list);
void	expand_env_var(t_list *token_list, t_env **env_lst, int status);
t_ast	*build_tree(t_list *token_list);

//utils
char	**get_args(t_list *token_list);
void	remove_quotes(void *content);
void	remove_quotes(void *content);
char	*mask_single_quoted_part(char *s);
char	*mask_quoted_part(char *s);
int		ft_isoperater(char c);

#endif