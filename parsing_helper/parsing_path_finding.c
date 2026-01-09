/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_path_finding.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:49:26 by mrojouan          #+#    #+#             */
/*   Updated: 2026/01/09 16:20:20 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>
#include <stdio.h>
static char *join_path(char *dir, char *cmd)
{
	char *tmp;
	char *final;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	final = ft_strjoin(tmp, cmd);
	if (!final)
		return (NULL);
	free(tmp);
	return (final);
}

static char **get_env_path(char *env_path)
{
	int i;
	char **paths;

	i = 0;
	while (env_path[i] != '/')
		i++;
	paths = ft_split(env_path + i, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char *find_path(char *cmd, char **envp)
{
	char **paths;
	char *path;
	int i;
	
	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	paths = get_env_path(envp[38]);
	i = 0;
	while (paths[i])
	{
		path = join_path(paths[i], cmd);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}
