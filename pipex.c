/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:53:58 by mrojouan          #+#    #+#             */
/*   Updated: 2026/01/08 15:43:39 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int main(int ac, char **av, char **envp)
{
	int fd_in;
	int pipe_fd[2];
	char **cmd1;
	char **cmd2;

	
	fd_in = open(av[1], O_RDONLY);
	if (!fd_in)
		return (0);
	cmd1 = ft_split(av[2], ' ');
	cmd2 = ft_split(av[3], ' ');
	dup2(fd_in, STDIN_FILENO);
	// dup2(pipe[1], STDOUT_FILENO);
	close(fd_in);
}