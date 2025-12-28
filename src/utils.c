/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/27 00:18:12 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cleanup_gnl(void);
void	free_parts(char **parts);
t_scene	**get_scene_cleanup_ptr(void);
char	***get_parts_cleanup_ptr(void);
char	**get_line_cleanup_ptr(void);

void	error_exit(char *msg)
{
	write(2, "Error\n", 6);
	if (msg)
	{
		while (*msg)
			write(2, msg++, 1);
		write(2, "\n", 1);
	}
	cleanup_gnl();
	if (*get_line_cleanup_ptr())
	{
		free(*get_line_cleanup_ptr());
		*get_line_cleanup_ptr() = NULL;
	}
	if (*get_parts_cleanup_ptr())
	{
		free_parts(*get_parts_cleanup_ptr());
		*get_parts_cleanup_ptr() = NULL;
	}
	if (*get_scene_cleanup_ptr())
	{
		free_scene(*get_scene_cleanup_ptr());
		free(*get_scene_cleanup_ptr());
		*get_scene_cleanup_ptr() = NULL;
	}
	exit(1);
}

static void	free_objects(t_object *obj)
{
	t_object	*tmp;

	while (obj)
	{
		tmp = obj->next;
		if (obj->data)
			free(obj->data);
		free(obj);
		obj = tmp;
	}
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free_objects(scene->objects);
}
