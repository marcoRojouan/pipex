/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:19:18 by loup              #+#    #+#             */
/*   Updated: 2026/01/30 11:38:07 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	cmd_error(char *cmd, t_path *path)
{
	int cmd_len;

	cmd_len = ft_strlen(cmd);
	write(2, cmd, cmd_len);
	write(2, ": command not found\n", 20);
	free(path->path);
	if (path->cmd1)
		free_all(path->cmd1);
	if (path->cmd2)
		free_all(path->cmd2);
	exit(127);
}

int		get_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
