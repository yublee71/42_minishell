/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:59:05 by yublee            #+#    #+#             */
/*   Updated: 2024/08/15 15:40:42 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	add_random_str_to_str(char *buf, size_t size, char *s, size_t rand)
{
	char	random_code[1024];
	char	tmp_buf[1];
	size_t	len;
	size_t	i;
	int		fd;

	if (rand + 1 > 1024)
		return ;
	len = ft_strlen(s) + rand;
	if (len + 1 > size)
		return ;
	ft_strlcpy(buf, s, size);
	fd = open("/dev/urandom", O_RDONLY);
	i = 0;
	while (read(fd, tmp_buf, 1) && i < rand)
		if (ft_isalnum(tmp_buf[0]))
			random_code[i++] = tmp_buf[0];
	close(fd);
	ft_strncat(buf, random_code, rand);
}

static void	read_til_delimiter(char *delimiter, t_info *info)
{
	char	*buf;
	int		tty_fd;
	int		new_fd;
	char	filename[FILENAME_MAX];

	add_random_str_to_str(filename, FILENAME_MAX, "/tmp/heredoc_input", 6);
	tty_fd = open("/dev/tty", O_RDONLY);
	new_fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (tty_fd < 0 || new_fd < 0)
		exit_with_message("open", EXIT_FAILURE, info);
	while (1)
	{
		write(1, "> ", 2);
		buf = get_next_line(tty_fd); //readline instead?
		if (!ft_strncmp(buf, delimiter, ft_strlen(delimiter)))
			break ;
		write(new_fd, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	new_fd = open(filename, O_RDWR);
	if (new_fd < 0)
		exit_with_message("open", EXIT_FAILURE, info);
	if (dup2(new_fd, STDIN_FILENO) < 0)
		exit_with_message("here doc", EXIT_FAILURE, info);
	close(tty_fd);
	close(new_fd);
	unlink(filename);
} //TODO: refactor with readline

static void	dup_redir_input_to_stdin(t_ast *in_node, t_info *info)
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

void	set_stdin(int i, t_ast *cmd, t_info *info)
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
		dup_redir_input_to_stdin(in_node, info);
		in_node = in_node->left->left;
	}
}
