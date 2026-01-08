/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:00:40 by mrojouan          #+#    #+#             */
/*   Updated: 2026/01/08 15:57:40 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*duplicata;
	int		i;
	int		len;

	len = ft_strlen(s);
	duplicata = NULL;
	duplicata = malloc(sizeof(char) * len + 1);
	if (!duplicata)
		return (0);
	i = 0;
	while (i < len)
	{
		duplicata[i] = s[i];
		i++;
	}
	duplicata[i] = '\0';
	return (duplicata);
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
	char *cmd_dup;
	int i;
	
	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, "/"))
	{
		if (access(cmd, X_OK) == 0)
		{
			cmd_dup = ft_strdup(cmd);
			return (cmd);
		}
		else
			return (NULL);
	}
	paths = get_env_path(envp[2]);
	i = 0;

		
}
