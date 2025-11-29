/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/11/30 01:11:51 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ray_new(t_vec3 origin, t_vec3 dir)
{
	t_ray	r;

	r.origin = origin;
	r.dir = dir;
	return (r);
}

t_vec3	ray_at(t_ray r, double t)
{
	return (vec3_add(r.origin, vec3_scale(r.dir, t)));
}
