/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yublee <yublee@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:59:19 by yublee            #+#    #+#             */
/*   Updated: 2024/07/30 16:08:32 by yublee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_before_exit(t_info	info)
{
	if (info.fds)
		free_fds(info.fds, info.cmd_cnt - 1);
	if (info.cmd_list)
		ft_lstclear(info.cmd_list, del);
	if (info.root)
		btree_apply_suffix(info.root, free_node);
}

void	exit_with_message(char *str, int exit_no, t_info info)
{
	if (str)
	{
		if (exit_no == 127)
		{
			write(2, str, ft_strlen(str));
			write(2, ": command not found\n", 20);
			free(str);
		}
		else
			perror(str);
	}
	free_before_exit(info);
	exit(exit_no);
}

void	free_str_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int	free_fds(int **fds, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(fds[j++]);
	free(fds);
	return (1);
}

void	add_random_str_to_str(char *buf, size_t buf_size, char *str, size_t rand_count)
{
	char	random_code[1024];
	char	tmp_buf[1];
	size_t	len;
	size_t	i;
	int		fd;

	if (rand_count + 1 > 1024)
		return ;
	len = ft_strlen(str) + rand_count;
	if (len + 1 > buf_size)
		return ;
	ft_strlcpy(buf, str, buf_size);
	fd = open("/dev/urandom", O_RDONLY);
	i = 0;
	while (read(fd, tmp_buf, 1) && i < rand_count)
		if (ft_isalnum(tmp_buf[0]))
			random_code[i++] = tmp_buf[0];
	close(fd);
	ft_strncat(buf, random_code, rand_count);
}