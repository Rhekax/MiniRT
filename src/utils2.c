/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:00:00 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/29 00:00:00 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	**get_scene_cleanup_ptr(void);
char	***get_parts_cleanup_ptr(void);
char	**get_line_cleanup_ptr(void);

void	set_scene_cleanup(t_scene *scene)
{
	*get_scene_cleanup_ptr() = scene;
}

void	set_current_parts(char **parts)
{
	*get_parts_cleanup_ptr() = parts;
}

void	set_current_line(char *line)
{
	*get_line_cleanup_ptr() = line;
}
