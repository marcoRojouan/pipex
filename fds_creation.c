/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:41:45 by mrojouan          #+#    #+#             */
/*   Updated: 2026/01/12 16:46:29 by mrojouan         ###   ########.fr       */
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