/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 00:00:00 by yenyilma          #+#    #+#             */
/*   Updated: 2024/12/24 00:00:00 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	is_whitespace_line(char *line)
{
	if (!line)
		return (1);
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\r')
			return (0);
		line++;
	}
	return (1);
}

int	is_empty_file(int fd)
{
	char	*line;
	int		has_content;

	has_content = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!is_whitespace_line(line))
			has_content = 1;
		free(line);
		if (has_content)
			break ;
		line = get_next_line(fd);
	}
	while (line)
	{
		line = get_next_line(fd);
		if (line)
			free(line);
	}
	return (!has_content);
}
