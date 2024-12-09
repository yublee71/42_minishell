/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:02:47 by yublee            #+#    #+#             */
/*   Updated: 2024/12/09 20:24:13 by yublee           ###   ########.fr       */
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
	ft_memset(random_code, 0, 1024);
	while (read(fd, tmp_buf, 1) && i < rand)
		if (ft_isalnum(tmp_buf[0]))
			random_code[i++] = tmp_buf[0];
	close(fd);
	ft_strncat(buf, random_code, rand);
}

static void	write_until_delimiter(int new_fd, char *delimiter)
{
	char	*buf;

	while (!g_sigint_received)
	{
		buf = readline("> ");
		if (buf)
		{
			if (ft_strlen(buf) == ft_strlen(delimiter)
				&& !ft_strncmp(buf, delimiter, ft_strlen(delimiter)))
			{
				if (!g_sigint_received)
					free(buf);
				return ;
			}
			write(new_fd, buf, ft_strlen(buf));
			write(new_fd, "\n", 1);
			free(buf);
		}
		else
			g_sigint_received = 1;
	}
	if (!g_sigint_received)
		free(buf);
}

void	handle_heredoc_input(char *delimiter, t_info *info)
{
	int		new_fd;
	int		tty_fd;
	char	filename[FILENAME_MAX];

	signal(SIGINT, handle_sigint_heredoc);
	ft_memset(filename, 0, FILENAME_MAX);
	add_random_str_to_str(filename, FILENAME_MAX, "/tmp/heredoc_input", 6);
	new_fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0666);
	tty_fd = open("/dev/tty", O_RDONLY);
	if (tty_fd < 0 || new_fd < 0)
		exit_with_message("open", EXIT_FAILURE, info);
	if (dup2(tty_fd, STDIN_FILENO) < 0)
		exit_with_message("heredoc", EXIT_FAILURE, info);
	write_until_delimiter(new_fd, delimiter);
	new_fd = open(filename, O_RDWR);
	if (new_fd < 0)
		exit_with_message("open", EXIT_FAILURE, info);
	if (dup2(new_fd, STDIN_FILENO) < 0)
		exit_with_message("heredoc", EXIT_FAILURE, info);
	close(new_fd);
	close(tty_fd);
	unlink(filename);
}
