/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loup <loup@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:18:28 by loup              #+#    #+#             */
/*   Updated: 2026/01/29 14:18:41 by loup             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void focking_parsing(t_path *path, t_fds *fds, char **av)
{
	fds->fd_in = create_fd_in(av[1]);
	if (fds->fd_in == -1)
		exit(1);
	fds->fd_out = create_fd_out(av[4]);
	if (fds->fd_out == -1)
	{
		close(fds->fd_in);
		exit(1);
	}
	path->cmd1 = ft_split(av[2], ' ');
	if (!path->cmd1 || !path->cmd1[0])
		cmd_error("", path);
	path->cmd2 = ft_split(av[3], ' ');
	if (!path->cmd2 || !path->cmd2[0])
	{
		free_all(path->cmd1);
		cmd_error("", path);
	}
}