/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:00:00 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/29 00:00:00 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	**get_scene_cleanup_ptr(void)
{
	static t_scene	*scene = NULL;

	return (&scene);
}

char	***get_parts_cleanup_ptr(void)
{
	static char	**parts = NULL;

	return (&parts);
}

char	**get_line_cleanup_ptr(void)
{
	static char	*line = NULL;

	return (&line);
}
