/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/11/30 01:11:51 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	clamp_value(double val)
{
	if (val < 0.0)
		return (0.0);
	if (val > 1.0)
		return (1.0);
	return (val);
}

t_color	color_clamp(t_color c)
{
	t_color	result;

	result.r = clamp_value(c.r);
	result.g = clamp_value(c.g);
	result.b = clamp_value(c.b);
	return (result);
}

int	color_to_int(t_color c)
{
	int	r;
	int	g;
	int	b;

	c = color_clamp(c);
	r = (int)(c.r * 255);
	g = (int)(c.g * 255);
	b = (int)(c.b * 255);
	return (r << 16 | g << 8 | b);
}
