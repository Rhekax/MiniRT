/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 00:00:00 by yenyilma          #+#    #+#             */
/*   Updated: 2024/12/24 00:00:00 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	validate_normal_vector(t_vec3 vec, char *error_msg);

static void	validate_cyl_dims(t_cylinder *cyl)
{
	if (cyl->diameter <= 0.0 || cyl->height <= 0.0)
	{
		free(cyl);
		error_exit("Cylinder diameter and height must be positive");
	}
}

t_cylinder	*create_cylinder(char **parts)
{
	t_cylinder	*cyl;
	t_vec3		axis;

	cyl = malloc(sizeof(t_cylinder));
	if (!cyl)
		error_exit("Memory allocation failed");
	cyl->center = parse_vec3(parts[1]);
	axis = parse_vec3(parts[2]);
	validate_normal_vector(axis, "Cylinder axis must be normalized");
	cyl->axis = vec3_normalize(axis);
	cyl->diameter = ft_atof(parts[3]);
	cyl->height = ft_atof(parts[4]);
	validate_cyl_dims(cyl);
	cyl->color = parse_color(parts[5]);
	return (cyl);
}
