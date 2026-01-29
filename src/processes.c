/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loup <loup@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 14:09:42 by loup              #+#    #+#             */
/*   Updated: 2026/01/29 14:21:26 by loup             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void close_all(t_fds *fds)
{
	if (fds->fd_pipe[0] != -1)
        close(fds->fd_pipe[0]);
    if (fds->fd_pipe[1] != -1)
        close(fds->fd_pipe[1]);
    if (fds->fd_in != -1)
        close(fds->fd_in);
    if (fds->fd_out != -1)
        close(fds->fd_out);
}

void	executions(t_path *path, char **envp, int i)
{	
	if (i == 0)
	{
		path->path = find_path(path->cmd1[0], envp);
		if (!path->path)
		{
        	cmd_error(path->cmd1[0], path);
		}
		execve(path->path, path->cmd1, envp);
	}
	else
	{
		path->path = find_path(path->cmd2[0], envp);
		if (!path->path)
		{
        	cmd_error(path->cmd2[0], path);
		}
		execve(path->path, path->cmd2, envp);
	}
	perror("execve");
	free(path->path);
    free_all(path->cmd1);
    free_all(path->cmd2);
	exit(127);
}	

void	child_process(t_path *path, t_fds *fds, char **envp, int i)
{
	if (i == 0)
	{
		dup2(fds->fd_in, STDIN_FILENO);
		dup2(fds->fd_pipe[1], STDOUT_FILENO);
	}
	else
	{
		dup2(fds->fd_pipe[0], STDIN_FILENO);
		dup2(fds->fd_out, STDOUT_FILENO);
	}
	close_all(fds);
	executions(path, envp, i);
}

void	fork_process(t_path *path, t_fds *fds, char **envp, int pid[2])
{
	int	i;

	i = 0;
	while (i < 2)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			perror("fork");
			if (i == 1)
				waitpid(pid[0], NULL, 0);
			exit(1);
		}
		if (pid[i] == 0)
			child_process(path, fds, envp, i);
		i++;
	}
}

int	wait_processes(int pid[2])
{
	int	status[2];

	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	if (WIFEXITED(status[1]))
		return (WEXITSTATUS(status[1]));
	if (WIFEXITED(status[0]))
		return (WEXITSTATUS(status[0]));
	return (1);
}