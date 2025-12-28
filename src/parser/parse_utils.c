/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/27 00:49:25 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_space(char c);
int	is_valid_number(const char *str);

static int	parse_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

static double	parse_integer_part(const char **str)
{
	double	result;

	result = 0;
	while (**str >= '0' && **str <= '9')
		result = result * 10 + (*(*str)++ - '0');
	return (result);
}

static double	parse_fractional_part(const char **str)
{
	double	result;
	double	fraction;

	result = 0;
	if (**str == '.')
		(*str)++;
	fraction = 0.1;
	while (**str >= '0' && **str <= '9')
	{
		result += (*(*str)++ - '0') * fraction;
		fraction *= 0.1;
	}
	return (result);
}

double	ft_atof(const char *str)
{
	double	result;
	int		sign;

	while (is_space(*str))
		str++;
	if (!is_valid_number(str))
		error_exit("Error\nInvalid number format");
	sign = parse_sign(&str);
	result = parse_integer_part(&str);
	result += parse_fractional_part(&str);
	return (result * sign);
}
