/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:53:58 by mrojouan          #+#    #+#             */
/*   Updated: 2026/01/15 14:27:27 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>
#include <sys/types.h>
#include <sys/wait.h>

void close_all(int *fd_pipe, int fd_in, int fd_out)
{
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	close(fd_in);
	close(fd_out);
}

int main(int ac, char **av, char **envp)
{
	int fd_in;
	int fd_out;
	int fd_pipe[2];
	int pid1, pid2;
	char **cmd1;
	char **cmd2;
	char *path;
	(void)ac;
	
	fd_in = create_fd_in(av[1]);
	fd_out = create_fd_out(av[4]);
	cmd1 = ft_split(av[2], ' ');
	cmd2 = ft_split(av[3], ' ');
	pipe(fd_pipe);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(fd_in, 0);
		dup2(fd_pipe[1], 1);
		close_all(fd_pipe, fd_in, fd_out);
		path = find_path(cmd1[0], envp);
		execve(path, cmd1, envp);
		exit(1);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd_pipe[0], 0);
    	dup2(fd_out, 1);
    	close_all(fd_pipe, fd_in, fd_out);
    	path = find_path(cmd2[0], envp);
    	execve(path, cmd2, envp);
	}
	close_all(fd_pipe, fd_in, fd_out);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
	free(cmd1);
	free(cmd2);
}
