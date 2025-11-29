/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/11/30 01:29:34 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color	apply_ambient(t_color obj_color, t_ambient ambient)
{
	t_color	result;

	result = color_mult(obj_color, ambient.color);
	result = color_scale(result, ambient.ratio);
	return (result);
}

static double	max_d(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

static t_color	apply_diffuse(t_hit *hit, t_light light, t_vec3 light_dir)
{
	double	diff;
	t_color	result;

	diff = max_d(0.0, vec3_dot(hit->normal, light_dir));
	result = color_mult(hit->color, light.color);
	result = color_scale(result, light.ratio * diff);
	return (result);
}

t_color	compute_lighting(t_hit *hit, t_scene *scene, t_vec3 light_dir)
{
	t_color	ambient;
	t_color	diffuse;
	t_color	final;

	ambient = apply_ambient(hit->color, scene->ambient);
	diffuse = apply_diffuse(hit, scene->light, light_dir);
	final = color_add(ambient, diffuse);
	return (color_clamp(final));
}
