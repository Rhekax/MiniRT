/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/11/30 01:29:34 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define BUFFER_SIZE 42

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = '\0';
	free(s1);
	return (result);
}

static char	*extract_line(char **buffer)
{
	char	*line;
	char	*new_buf;
	int		i;
	int		start;

	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = -1;
	while ((*buffer)[++i] && (*buffer)[i] != '\n')
		line[i] = (*buffer)[i];
	line[i] = '\0';
	start = i;
	if ((*buffer)[i] == '\n')
		start = i + 1;
	new_buf = ft_substr(*buffer, start, ft_strlen(*buffer) - start);
	free(*buffer);
	*buffer = new_buf;
	return (line);
}

static int	has_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*read_and_join(int fd, char *buffer)
{
	char	tmp[BUFFER_SIZE + 1];
	int		bytes;

	bytes = 1;
	while (bytes > 0 && !has_newline(buffer))
	{
		bytes = read(fd, tmp, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buffer);
			return (NULL);
		}
		tmp[bytes] = '\0';
		buffer = ft_strjoin_gnl(buffer, tmp);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		buffer = malloc(1);
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	buffer = read_and_join(fd, buffer);
	if (!buffer || ft_strlen(buffer) == 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	return (extract_line(&buffer));
}
