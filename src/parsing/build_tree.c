/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 23:39:34 by yublee            #+#    #+#             */
/*   Updated: 2024/08/15 15:24:38 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_ast	*parse_redirection_out(t_list *head)
{
	t_ast	*node;
	t_list	*current;
	t_token	*token;

	if (!head)
		return (NULL);
	current = head;
	token = (t_token *)current->content;
	while (current && token->type != TK_PIPE)
	{
		token = (t_token *)current->content;
		if (token->type == TK_OUTPUT || token->type == TK_APPEND)
		{
			node = ast_new_node(token);
			node->right = ast_new_node((t_token *)current->next->content);
			node->left = NULL;
			node->right->right = parse_redirection_out(current->next->next);
			node->right->left = NULL;
			return (node);
		}
		current = current->next;
	}
	return (NULL);
}

static t_ast	*parse_redirection_in(t_list *head)
{
	t_ast	*node;
	t_list	*current;
	t_token	*token;

	if (!head)
		return (NULL);
	current = head;
	token = (t_token *)current->content;
	while (current && token->type != TK_PIPE)
	{
		token = (t_token *)current->content;
		if (token->type == TK_INPUT || token->type == TK_HEREDOC)
		{
			node = ast_new_node(token);
			node->left = ast_new_node((t_token *)current->next->content);
			node->right = NULL;
			node->left->left = parse_redirection_in(current->next->next);
			node->left->right = NULL;
			return (node);
		}
		current = current->next;
	}
	return (NULL);
}

static t_ast	*parse_command(t_list *head)
{
	t_ast	*node;
	t_list	*current;
	t_token	*token;

	if (!head)
		return (NULL);
	current = head;
	token = (t_token *)current->content;
	while (current && token->type != TK_PIPE)
	{
		token = (t_token *)current->content;
		if (token->type == TK_WORD)
		{
			node = ast_new_node(token);
			node->args = get_args(current);
			node->left = parse_redirection_in(head);
			node->right = parse_redirection_out(head);
			return (node);
		}
		current = current->next;
	}
	node = ast_new_node(NULL);
	node->left = parse_redirection_in(head);
	node->right = parse_redirection_out(head);
	return (node);
}

static t_ast	*parse_pipeline(t_list *head)
{
	t_ast	*node;
	t_list	*current;
	t_token	*token;

	if (!head)
		return (NULL);
	current = head;
	while (current)
	{
		token = (t_token *)current->content;
		if (token->type == TK_PIPE)
		{
			node = ast_new_node(token);
			node->left = parse_command(head);
			node->right = parse_pipeline(current->next);
			return (node);
		}
		current = current->next;
	}
	return (parse_command(head));
}

t_ast	*build_tree(t_list *token_list)
{
	t_ast	*root;

	if (!token_list)
		return (NULL);
	root = parse_pipeline(token_list);
	return (root);
}
