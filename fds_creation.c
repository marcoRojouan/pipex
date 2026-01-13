/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:41:45 by mrojouan          #+#    #+#             */
/*   Updated: 2026/01/13 14:21:31 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int create_fd_in(char *infile)
{
	int fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
	{
		perror(infile);
		exit(1);
	}
	return (fd);
}

int create_fd_out(char *outfile)
{
	int fd;
	fd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(outfile);
		exit(1);
	}
	return (fd);
}