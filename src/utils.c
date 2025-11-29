/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/11/30 01:29:34 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	error_exit(char *msg)
{
	write(2, "Error\n", 6);
	if (msg)
	{
		while (*msg)
			write(2, msg++, 1);
		write(2, "\n", 1);
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
