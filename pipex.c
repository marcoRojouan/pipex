/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:53:58 by mrojouan          #+#    #+#             */
/*   Updated: 2026/01/30 14:17:33 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	processes(t_path *path, t_fds *fds, char **envp)
{
	int pid[2];
	int status_code;

	fork_process(path, fds, envp, pid);
	close_all(fds);
	status_code = wait_processes(pid);
	return (status_code);
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
