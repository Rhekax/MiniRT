/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/11/30 01:11:51 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color_new(double r, double g, double b)
{
	t_color	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

t_color	color_add(t_color a, t_color b)
{
	return (color_new(a.r + b.r, a.g + b.g, a.b + b.b));
}

t_color	color_mult(t_color a, t_color b)
{
	return (color_new(a.r * b.r, a.g * b.g, a.b * b.b));
}

t_color	color_scale(t_color c, double t)
{
	return (color_new(c.r * t, c.g * t, c.b * t));
}
