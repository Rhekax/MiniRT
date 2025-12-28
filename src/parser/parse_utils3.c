/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:00:00 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/29 00:00:00 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_parts(char **parts)
{
	int	i;

	if (!parts)
		return ;
	i = 0;
	while (parts[i])
		free(parts[i++]);
	free(parts);
}

void	init_scene(t_scene *scene)
{
	scene->has_ambient = 0;
	scene->has_camera = 0;
	scene->has_light = 0;
	scene->objects = NULL;
	scene->object_count = 0;
}

int	check_extension(char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + len - 3, ".rt", 3) == 0);
}
