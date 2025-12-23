/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_common2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 00:00:00 by yenyilma          #+#    #+#             */
/*   Updated: 2024/12/24 00:00:00 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_valid_double(double val)
{
	if (val != val)
		return (0);
	if (val > 1e308 || val < -1e308)
		return (0);
	return (1);
}

static int	validate_vec3_values(t_vec3 v)
{
	if (!check_valid_double(v.x) || !check_valid_double(v.y)
		|| !check_valid_double(v.z))
		return (0);
	return (1);
}

static int	validate_rgb_values(int *rgb)
{
	if (rgb[0] < 0 || rgb[0] > 255)
		return (0);
	if (rgb[1] < 0 || rgb[1] > 255)
		return (0);
	if (rgb[2] < 0 || rgb[2] > 255)
		return (0);
	return (1);
}

void	parse_vec3_values(char **parts, t_vec3 *v)
{
	v->x = ft_atof(parts[0]);
	v->y = ft_atof(parts[1]);
	v->z = ft_atof(parts[2]);
	if (!validate_vec3_values(*v))
		error_exit("Invalid vector values");
}

void	parse_color_values(char **parts, t_color *c)
{
	int		rgb[3];

	rgb[0] = (int)ft_atof(parts[0]);
	rgb[1] = (int)ft_atof(parts[1]);
	rgb[2] = (int)ft_atof(parts[2]);
	if (!validate_rgb_values(rgb))
		error_exit("Color values must be in range [0-255]");
	c->r = rgb[0] / 255.0;
	c->g = rgb[1] / 255.0;
	c->b = rgb[2] / 255.0;
}
