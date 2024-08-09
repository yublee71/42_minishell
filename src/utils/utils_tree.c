/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:56:33 by yublee            #+#    #+#             */
/*   Updated: 2024/08/09 20:03:59 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tree_print_node(t_ast *node)
{
	const char		*type_names[8] = {
		"WORD", "PIPE", "INPUT", "OUTPUT", "APPEND",
		"HEREDOC", "FILE", NULL};
	int				type;
	int				type_val;
	int				i;
	char	**args;

	ft_printf("val: [%s]\n", node->value);
	type = node->type;
	i = 0;
	type_val = 1;
	while (!(type == type_val) && i < 7)
	{
		type_val = type_val << 1;
		i++;
	}
	ft_printf("type: %s\n", type_names[i]);
	if (node->args)
	{
		args = node->args;
		ft_printf("args: ");
		while (*args)
			ft_printf("%s, ", *args++);
		ft_printf("\n");
	}
}

void	tree_free_node(t_ast *node)
{
	if (node->type == TK_WORD || node->type == TK_FILE)
	{
		if (node->args)
			free_array((void **)node->args);
		else if (node->value)
		{
			free(node->value);
			node->value = NULL;
		}
	}
	free(node);
	node = NULL;
}

t_ast	*ast_new_node(t_token *token)
{
	t_ast	*node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (!node)
		exit(EXIT_FAILURE);
	node->left = NULL;
	node->right = NULL;
	node->args = NULL;
	if (!token)
	{
		node->type = TK_WORD;
		node->value = NULL;
	}
	else
	{
		node->type = token->type;
		node->value = token->value;
	}
	return (node);
}

void	tree_apply_infix(t_ast *node, void (*applyf)(t_ast *))
{
	if (node == NULL)
		return ;
	tree_apply_infix(node->left, applyf);
	applyf(node);
	tree_apply_infix(node->right, applyf);
}

void	tree_apply_suffix(t_ast *node, void (*applyf)(t_ast *))
{
	if (node == NULL)
		return ;
	tree_apply_suffix(node->left, applyf);
	tree_apply_suffix(node->right, applyf);
	applyf(node);
}
