/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/11/30 01:29:34 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_ambient(t_scene *scene, char **parts)
{
	if (scene->has_ambient)
		error_exit("Duplicate ambient light");
	if (!parts[1] || !parts[2])
		error_exit("Invalid ambient format");
	scene->ambient.ratio = ft_atof(parts[1]);
	scene->ambient.color = parse_color(parts[2]);
	if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
		error_exit("Ambient ratio must be [0.0, 1.0]");
	scene->has_ambient = 1;
}

void	parse_camera(t_scene *scene, char **parts)
{
	if (scene->has_camera)
		error_exit("Duplicate camera");
	if (!parts[1] || !parts[2] || !parts[3])
		error_exit("Invalid camera format");
	scene->camera.pos = parse_vec3(parts[1]);
	scene->camera.dir = vec3_normalize(parse_vec3(parts[2]));
	scene->camera.fov = ft_atof(parts[3]);
	if (scene->camera.fov < 0.0 || scene->camera.fov > 180.0)
		error_exit("FOV must be [0, 180]");
	scene->has_camera = 1;
}

void	parse_light(t_scene *scene, char **parts)
{
	if (scene->has_light)
		error_exit("Duplicate light");
	if (!parts[1] || !parts[2])
		error_exit("Invalid light format");
	scene->light.pos = parse_vec3(parts[1]);
	scene->light.ratio = ft_atof(parts[2]);
	if (parts[3])
		scene->light.color = parse_color(parts[3]);
	else
		scene->light.color = color_new(1.0, 1.0, 1.0);
	if (scene->light.ratio < 0.0 || scene->light.ratio > 1.0)
		error_exit("Light ratio must be [0.0, 1.0]");
	scene->has_light = 1;
}
