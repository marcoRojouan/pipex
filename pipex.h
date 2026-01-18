/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:55:47 by mrojouan          #+#    #+#             */
/*   Updated: 2026/01/18 15:52:01 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_path
{
	char	**cmd1;
	char	**cmd2;
	char	*path;
} 				t_path;

typedef struct s_fds
{
	int	fd_in;
	int	fd_out;
	int	fd_pipe[2];
} 				t_fds;

char	**ft_split(char *s, char c);
char 	*find_path(char *cmd, char **envp);
char	*ft_strdup(char *s);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);

int		create_fd_in(char *infile);
int		create_fd_out(char *outfile);
int		ft_strlen(char *str);

void	free_all(char **tab);

#endif