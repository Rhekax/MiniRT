/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_common.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/22 21:33:42 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_vec3_values(char **parts, t_vec3 *v);
void	parse_color_values(char **parts, t_color *c);

t_vec3	parse_vec3(char *str)
{
	char	**parts;
	t_vec3	v;

	if (!str || !*str)
		error_exit("Invalid vector format");
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2])
	{
		free_parts(parts);
		error_exit("Invalid vector format");
	}
	if (!*parts[0] || !*parts[1] || !*parts[2])
	{
		free_parts(parts);
		error_exit("Invalid vector format");
	}
	parse_vec3_values(parts, &v);
	free_parts(parts);
	return (v);
}

t_color	parse_color(char *str)
{
	char	**parts;
	t_color	c;

	if (!str || !*str)
		error_exit("Invalid color format");
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2])
	{
		free_parts(parts);
		error_exit("Invalid color format");
	}
	if (!*parts[0] || !*parts[1] || !*parts[2])
	{
		free_parts(parts);
		error_exit("Invalid color format");
	}
	parse_color_values(parts, &c);
	free_parts(parts);
	return (c);
}

void	validate_normal_vector(t_vec3 vec, char *error_msg)
{
	double	magnitude;

	if (vec.x < -1.0 || vec.x > 1.0 || vec.y < -1.0 || vec.y > 1.0
		|| vec.z < -1.0 || vec.z > 1.0)
		error_exit(error_msg);
	magnitude = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	if (magnitude < EPSILON)
		error_exit("Direction vector cannot be zero");
	if (magnitude < 0.9 || magnitude > 1.1)
		error_exit(error_msg);
}

void	add_object(t_scene *scene, t_object *new_obj)
{
	t_object	*tmp;

	if (!scene->objects)
	{
		scene->objects = new_obj;
		return ;
	}
	tmp = scene->objects;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_obj;
}
