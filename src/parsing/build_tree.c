/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 23:39:34 by yublee            #+#    #+#             */
/*   Updated: 2024/08/09 20:13:09 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	count_args(t_list *token_list)
{
	int		cnt;
	t_list	*current;
	t_token	*token;

	cnt = 0;
	current = token_list;
	token = (t_token *)current->content;
	while (current && token->type != TK_PIPE)
	{
		token = (t_token *)current->content;
		if (token->type == TK_WORD)
			cnt++;
		current = current->next;
	}
	return (cnt);
}

static char	**get_args(t_list *token_list)
{
	char	**args;
	int		arg_count;
	int		i;
	t_list	*current;
	t_token	*token;

	if (!token_list)
		return (NULL);
	arg_count = count_args(token_list);
	args = (char **)malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		exit(EXIT_FAILURE);
	i = 0;
	current = token_list;
	token = (t_token *)current->content;
	while (current && token->type != TK_PIPE)
	{
		token = (t_token *)current->content;
		if (token->type == TK_WORD)
			args[i++] = token->value;
		current = current->next;
	}
	args[i] = NULL;
	return (args);
}

static t_ast	*parse_redirection_out(t_list *token_list)
{
	t_ast	*tree_node;
	t_list	*current;
	t_token	*token;

	if (!token_list)
		return (NULL);
	current = token_list;
	token = (t_token *)current->content;
	while (current && token->type != TK_PIPE)
	{
		token = (t_token *)current->content;
		if (token->type == TK_OUTPUT || token->type == TK_APPEND)
		{
			tree_node = ast_new_node((t_token *)current->content);
			tree_node->right = ast_new_node((t_token *)current->next->content);
			tree_node->left = NULL;
			tree_node->right->right = parse_redirection_out(current->next->next);
			tree_node->right->left = NULL;
			return (tree_node);
		}
		current = current->next;
	}
	return (NULL);
}

static t_ast	*parse_redirection_in(t_list *token_list)
{
	t_ast	*tree_node;
	t_list	*current;
	t_token	*token;

	if (!token_list)
		return (NULL);
	current = token_list;
	token = (t_token *)current->content;
	while (current && token->type != TK_PIPE)
	{
		token = (t_token *)current->content;
		if (token->type == TK_INPUT || token->type == TK_HEREDOC)
		{
			tree_node = ast_new_node((t_token *)current->content);
			tree_node->left = ast_new_node((t_token *)current->next->content);
			tree_node->right = NULL;
			tree_node->left->left = parse_redirection_in(current->next->next);
			tree_node->left->right = NULL;
			return (tree_node);
		}
		current = current->next;
	}
	return (NULL);
}

static t_ast	*parse_command(t_list *token_list)
{
	t_ast	*tree_node;
	t_list	*start;
	t_list	*current;
	t_token	*token;

	if (!token_list)
		return (NULL);
	start = token_list;
	current = token_list;
	token = (t_token *)current->content;
	while (current && token->type != TK_PIPE)
	{
		token = (t_token *)current->content;
		if (token->type == TK_WORD)
		{
			tree_node = ast_new_node(token);
			tree_node->args = get_args(current);
			tree_node->left = parse_redirection_in(start);
			tree_node->right = parse_redirection_out(start);
			return (tree_node);
		}
		current = current->next;
	}
	tree_node = ast_new_node(NULL);
	tree_node->left = parse_redirection_in(start);
	tree_node->right = parse_redirection_out(start);
	return (tree_node);
}

static t_ast	*parse_pipeline(t_list *token_list)
{
	t_ast	*tree_node;
	t_list	*start;
	t_list	*current;
	t_token	*token;

	if (!token_list)
		return (NULL);
	start = token_list;
	current = token_list;
	while (current)
	{
		token = (t_token *)current->content;
		if (token->type == TK_PIPE)
		{
			tree_node = ast_new_node(token);
			tree_node->left = parse_command(start);
			tree_node->right = parse_pipeline(current->next);
			return (tree_node);
		}
		current = current->next;
	}
	return (parse_command(start));
}

t_ast	*build_tree(t_list *token_list)
{
	t_ast	*root;
	if (!token_list)
		return (NULL);
	root = parse_pipeline(token_list);
	return (root);
}
