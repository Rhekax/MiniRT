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

static t_scene	*g_scene_cleanup = NULL;
static char		**g_parts_cleanup = NULL;
static char		*g_line_cleanup = NULL;

void	cleanup_gnl(void);
void	free_parts(char **parts);

void	set_scene_cleanup(t_scene *scene)
{
	g_scene_cleanup = scene;
}

void	set_current_parts(char **parts)
{
	g_parts_cleanup = parts;
}

void	set_current_line(char *line)
{
	g_line_cleanup = line;
}

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
	if (g_line_cleanup)
	{
		free(g_line_cleanup);
		g_line_cleanup = NULL;
	}
	if (g_parts_cleanup)
	{
		free_parts(g_parts_cleanup);
		g_parts_cleanup = NULL;
	}
	if (g_scene_cleanup)
	{
		free_scene(g_scene_cleanup);
		free(g_scene_cleanup);
		g_scene_cleanup = NULL;
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
