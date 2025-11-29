/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_common.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/11/30 01:29:34 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	parse_integer_part(const char **str)
{
	double	result;

	result = 0.0;
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10.0 + (**str - '0');
		(*str)++;
	}
	return (result);
}

static double	parse_decimal_part(const char **str)
{
	double	result;
	double	divisor;

	result = 0.0;
	divisor = 10.0;
	if (**str == '.')
	{
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			result += (**str - '0') / divisor;
			divisor *= 10.0;
			(*str)++;
		}
	}
	return (result);
}

double	ft_atof(const char *str)
{
	int		sign;
	double	result;

	if (!str)
		return (0.0);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = parse_integer_part(&str);
	result += parse_decimal_part(&str);
	return (sign * result);
}

t_vec3	parse_vec3(char *str)
{
	char	**parts;
	t_vec3	v;

	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2])
		error_exit("Invalid vector format");
	v.x = ft_atof(parts[0]);
	v.y = ft_atof(parts[1]);
	v.z = ft_atof(parts[2]);
	free(parts[0]);
	free(parts[1]);
	free(parts[2]);
	free(parts);
	return (v);
}

t_color	parse_color(char *str)
{
	char	**parts;
	t_color	c;

	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2])
		error_exit("Invalid color format");
	c.r = ft_atof(parts[0]) / 255.0;
	c.g = ft_atof(parts[1]) / 255.0;
	c.b = ft_atof(parts[2]) / 255.0;
	free(parts[0]);
	free(parts[1]);
	free(parts[2]);
	free(parts);
	return (c);
}
