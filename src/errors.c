/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loup <loup@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:19:18 by loup              #+#    #+#             */
/*   Updated: 2026/01/29 14:20:14 by loup             ###   ########.fr       */
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