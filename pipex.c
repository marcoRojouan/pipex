/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:53:58 by mrojouan          #+#    #+#             */
/*   Updated: 2026/01/28 16:44:59 by mrojouan         ###   ########.fr       */
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
void	cmd_error(char *cmd, t_path *path)
{
	int cmd_len;

	cmd_len = ft_strlen(cmd);
	write(2, cmd, cmd_len);
	write(2, ": command not found\n", 20);
	if (path->cmd1)
		free_all(path->cmd1);
	if (path->cmd2)
		free_all(path->cmd2);
	free(path->path);
	exit(127);
}

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
	if (!path->cmd1[0])
		cmd_error("", path);
	path->cmd2 = ft_split(av[3], ' ');
	if (!path->cmd2[0])
	{
		free_all(path->cmd1);
		cmd_error("", path);
	}
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

int	processes(t_path *path, t_fds *fds, char **envp)
{
	int i = 0;
	int pid[2];
	int status;

	while (i < 2)
	{
		pid[i] = fork();
		if (pid[i] == -1)
    		exit(1);
		if (pid[i] == 0)
		{
			if (i == 0)
			{
				dup2(fds->fd_in, 0);
				dup2(fds->fd_pipe[1], 1);
			}
			else 
			{
				dup2(fds->fd_pipe[0], 0);
    			dup2(fds->fd_out, 1);
			}
			close_all(fds);
			executions(path, envp, i);
		}	
		i++;
	}
	close_all(fds);
    waitpid(pid[0], NULL, 0);
    waitpid(pid[1], &status, 0);
	if (WIFEXITED(status))
    	return (WEXITSTATUS(status));
	return (1);
}

int main(int ac, char **av, char **envp)
{
	t_fds fds;
	t_path path;
	int code;
	
	fds.fd_pipe[0] = -1;
	fds.fd_pipe[1] = -1;
	path.cmd1 = NULL;
	path.cmd2 = NULL;
	path.path = NULL;
	if (ac != 5)
		return (1);
	focking_parsing(&path, &fds, av);
	if (pipe(fds.fd_pipe) == -1)
	{
		close_all(&fds);
		free_all(path.cmd1);
		free_all(path.cmd2);
		exit(1);
	}
	code = processes(&path, &fds, envp);
	close_all(&fds);
	free_all(path.cmd1);
	free_all(path.cmd2);
	free(path.path);
	return (code);
}
