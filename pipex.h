/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loup <loup@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 14:55:47 by mrojouan          #+#    #+#             */
/*   Updated: 2026/01/29 14:21:23 by loup             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

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
int		wait_processes(int pid[2]);

void	free_all(char **tab);
void	close_all(t_fds *fds);
void	cmd_error(char *cmd, t_path *path);
void	child_process(t_path *path, t_fds *fds, char **envp, int i);
void	fork_process(t_path *path, t_fds *fds, char **envp, int pid[2]);
void focking_parsing(t_path *path, t_fds *fds, char **av);

#endif