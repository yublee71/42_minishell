/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:37:53 by yublee            #+#    #+#             */
/*   Updated: 2024/08/11 17:45:08 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	read_til_delimiter(char *delimiter, t_info *info)
{
	char	*buf;
	int		tty_fd;
	int		new_fd;
	char	filename[FILENAME_MAX];

	add_random_str_to_str(filename, FILENAME_MAX, "/tmp/heredoc_input", 6);
	tty_fd = open("/dev/tty", O_RDONLY);
	new_fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (tty_fd < 0)
		exit_with_message("tty", EXIT_FAILURE, info);
	while (1)
	{
		write(1,"> ",2);
		buf = get_next_line(tty_fd); //readline instead?
		if (!ft_strncmp(buf, delimiter, ft_strlen(delimiter)))
			break ;
		write(new_fd, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	new_fd = open(filename, O_RDWR);
	if (dup2(new_fd, STDIN_FILENO) < 0)
		exit_with_message("here doc", EXIT_FAILURE, info);
	close(tty_fd);
	close(new_fd);
	unlink(filename);
}

static void	open_input(t_ast *in_node, t_info *info)
{
	int		fd_input;
	t_ast	*file_node;

	file_node = in_node->left;
	fd_input = -1;
	if (in_node->type == TK_HEREDOC)
		read_til_delimiter(file_node->value, info);
	else if (in_node->type == TK_INPUT)
	{
		fd_input = open(file_node->value, O_RDONLY);
		if (fd_input < 0 || dup2(fd_input, STDIN_FILENO) < 0)
			exit_with_message(file_node->value, EXIT_FAILURE, info);
		close(fd_input);
	}
}

static void	open_output(t_ast *out_node, t_info *info)
{
	int		fd_output;
	t_ast	*file_node;

	file_node = out_node->right;
	fd_output = -1;
	if (out_node->type == TK_OUTPUT)
		fd_output = open(file_node->value, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (out_node->type == TK_APPEND)
		fd_output = open(file_node->value, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (fd_output < 0 || dup2(fd_output, STDOUT_FILENO) < 0)
		exit_with_message(file_node->value, EXIT_FAILURE, info);
	close(fd_output);
}

void	get_input(int i, t_ast *cmd, t_info *info)
{
	t_ast	*in_node;

	if (i != 0 && i != -1)
	{
		close(info->fds[i - 1][WRITE_END]);
		if (dup2(info->fds[i - 1][READ_END], STDIN_FILENO) < 0)
			exit_with_message("dup2", EXIT_FAILURE, info);
		close(info->fds[i - 1][READ_END]);
	}
	in_node = cmd->left;
	while (in_node)
	{
		open_input(in_node, info);
		in_node = in_node->left->left;
	}
}

void	get_output(int i, t_ast *cmd, t_info *info)
{
	t_ast	*out_node;

	if (i != info->cmd_cnt - 1 && i != -1)
	{
		close(info->fds[i][READ_END]);
		if (dup2(info->fds[i][WRITE_END], STDOUT_FILENO) < 0)
			exit_with_message("dup2", EXIT_FAILURE, info);
		close(info->fds[i][WRITE_END]);
	}
	out_node = cmd->right;
	while (out_node)
	{
		open_output(out_node, info);
		out_node = out_node->right->right;
	}
}
