/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:00:40 by mrojouan          #+#    #+#             */
/*   Updated: 2026/01/15 14:15:21 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
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

char	*ft_strdup(char *s)
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

char	*ft_strjoin(char *s1, char *s2)
{
	int		s1len;
	int		s2len;
	int		i;
	int		j;
	char	*tab;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	tab = NULL;
	tab = malloc(sizeof(char) * (s1len + s2len) + 1);
	if (!tab)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
		tab[j++] = s1[i++];
	i = 0;
	while (s2[i])
		tab[j++] = s2[i++];
	tab[j] = 0;
	return (tab);
}
