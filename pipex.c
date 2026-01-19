/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:53:58 by mrojouan          #+#    #+#             */
/*   Updated: 2026/01/19 15:54:48 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void close_all(t_fds *fds)
{
	close(fds->fd_pipe[0]);
	close(fds->fd_pipe[1]);
	close(fds->fd_in);
	close(fds->fd_out);
}

void focking_parsing(t_path *path, t_fds *fds, char **av)
{
	fds->fd_in = create_fd_in(av[1]);
	fds->fd_out = create_fd_out(av[4]);
	path->cmd1 = ft_split(av[2], ' ');
	if (!path->cmd1)
		return ;
	path->cmd2 = ft_split(av[3], ' ');
	if (!path->cmd2)
		return ;
}

/** 
 * @param t_path path
 * @param char** envp
 * @param int i 
 * 
 * Finding the path for the shell commands 
 */
void	executions(t_path *path, char **envp, int i)
{	
	if (i == 0)
	{
		path->path = find_path(path->cmd1[0], envp);
		execve(path->path, path->cmd1, envp);
	}
	else
	{
		path->path = find_path(path->cmd2[0], envp);
		execve(path->path, path->cmd2, envp);
	}
	free_all(path->path);
	perror("MAIS CA VA PAS LA TETE");
	exit(127);
}	

void	processes(t_path *path, t_fds *fds, char **envp)
{
	int i = 0;
	int pid[2];

	while (i < 2)
	{
		pid[i] = fork();
		if (pid == 0)
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
			close_all(&fds);
			executions(&path, envp, i);
		}
	}

}

int main(int ac, char **av, char **envp)
{
	t_fds fds;
	t_path path;
	int pid1, pid2;
	(void)ac;
	
	focking_parsing(&path, &fds, av);
	pipe(fds.fd_pipe);
	processes(&path, &fds, envp);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
	free(path.cmd1);
	free(path.cmd2);
}
